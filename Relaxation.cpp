// Relaxation.cpp: implementation of the Relaxation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LatticeRelaxation.h"
#include "Relaxation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include <algorithm>

/**
 * Default constructor for Relaxation class
 */
Relaxation::~Relaxation()
{

}

/**
 * Parametrized constructor for Relaxation class
 *
 * Takes a pointer to CLatticeRelaxationDoc and ModelingOptions instance as parameters and sets their values 
 * to local member variables
 */
Relaxation::Relaxation(CLatticeRelaxationDoc* doc, ModelingOptions modelingOptions)
	: Modeling(doc), modelingOptions(modelingOptions), lattice(m_Doc->modelingProject->activeLattice), atomsDeque(lattice->atoms) 
{
	lattice = m_Doc->modelingProject->activeLattice;
	atomsDeque = lattice->atoms;
}

/**
 * Executes migration modelling process for an atom defined in modellingProject variable
 *
 * Modeling Scenario: migrating atom is immobile and traped along migration direction in a
 * given number of steps; On every step the lack lattice is relaxed to find configuration with
 * minimal energy
 *
 * Migrating atom is specified by m_Doc->modelingProject->migratingAtom
 * Migration final atom is m_Doc->modelingProject->migratingToPoint
 * Number of migration steps is m_Doc->modelingProject->migratingSteps
 *
 * Returns instance of MigrationResults class with information about modeling results
 */
MigrationResults Relaxation::migration(LPVOID pParam)
{
	// Prepare MigrationResults to fulfill and return it later in function
	MigrationResults migrationResults;

	ModelingProject* modelingProject = m_Doc->modelingProject;

	// Calculate migration step vector
	Vector migrationStep = modelingProject->migratingToPoint - modelingProject->migratingAtom->r;
	migrationStep /= modelingProject->migratingSteps;

	for (int i = 0; i <= modelingProject->migratingSteps; i++) {
		// Relax lattice for every step
		MigrationStepResults migrationStepResult = relaxLattice(pParam);

		// Save relaxation results information to migration results
		migrationStepResult.migratingAtomCoordinates = modelingProject->migratingAtom->r;
		migrationResults.migrationStepResults.push_back(migrationStepResult);

		// Set forces of all atoms to 0
		Lattice* lattice = m_Doc->modelingProject->activeLattice;
		std::deque<Atom*>& atomsDeque = lattice->atoms;
		std::deque<Atom*>::iterator atomsIterator;
		for (atomsIterator = atomsDeque.begin(); atomsIterator != atomsDeque.end(); atomsIterator++) {
			Atom* atom = *atomsIterator;
			atom->v = Vector(0,0,0);
		}

		// Move atom one step forward
		modelingProject->migratingAtom->r += migrationStep;
	}

	// Return migrating atom one step behind
	modelingProject->migratingAtom->r -= migrationStep;
	
	return migrationResults;
}

/**
 * Execute lattice relaxation modelling process
 *
 * Depending on modeling options set in modelingOptions member variable this method
 * execute modeling process wither with or without elastic corrections
 *
 * If we want to take dilatation volume into account, modelingOptions.calculateDilatationVolume
 * must be true. In this case this function calls correctShell() function
 * Otherwise relaxLattice() is called
 */
RelaxationResults Relaxation::relaxation(LPVOID pParam)
{
	if (!modelingOptions.calculateDilatationVolume) {
		// Relax crystallite without calculating dilatation volume and without elastic corrections
		// Just delegate calculations to relaxLattice() method
		return relaxLattice(pParam);
	} else {

		// Relax crystallite with elastic corrections; 
		// Their number is set in modelingOptions.elasticCorrectionsAmmount
		const int correctionsAmmount = modelingOptions.elasticCorrectionsAmmount;

		// On every correction step delegate calculation to correctShell() method
		RelaxationResults relaxationResults = correctShell(pParam);

		for (int i = 1; i < correctionsAmmount; i++) {
			RelaxationResults correctedRelaxationResults = correctShell(pParam);

			// Amend relaxation results taking in view new correction step
			relaxationResults.calculationTime += correctedRelaxationResults.calculationTime;
			relaxationResults.modelTime += correctedRelaxationResults.modelTime;
			relaxationResults.numberOfDempthings += correctedRelaxationResults.numberOfDempthings;
			relaxationResults.numberOfStemps += correctedRelaxationResults.numberOfStemps;
			relaxationResults.complexEnergyAfterRelaxationCorrected = correctedRelaxationResults.complexEnergyAfterRelaxation;
			relaxationResults.relaxationEnergy = relaxationResults.complexEnergyAfterRelaxationCorrected - relaxationResults.complexEnergyBeforeRelaxation;
		}

		return relaxationResults;
	}
}

/**
 * This method calculates relaxed atomistic configuration and after that corrects immutable shell
 * taking into account point defect dilatation volume
 *
 * For finding relaxed configuration delegates call to relaxLattice() method
 *
 * After that we calculate forces experiencing by shell atoms and calculate dilatation volume
 * from the difference of these forces before and after creating given point defect
 * 
 * Shifts atoms in immovable shell based on calculated dilatation volume
 */
RelaxationResults Relaxation::correctShell(LPVOID pParam) {

	// Find relaxed configuration
	RelaxationResults relaxationResults = relaxLattice(pParam);

	// Calculate forces experiencing by atoms in immovable shell
	resetShellForces();
	calculateForces(true);

	// Calculate dilatation volume
	double D11 = 0, D22 = 0, D33 = 0;
	for (std::deque<Atom*>::iterator atomsIterator = atomsDeque.begin(); atomsIterator != atomsDeque.end(); atomsIterator++) {
		Atom* atom = *atomsIterator;
		
		if (!atom->inShell) continue;

		Vector dF = atom->v - atom->vSaved;

		D11 += atom->r.x * dF.x;
		D22 += atom->r.y * dF.y;
		D33 += atom->r.z * dF.z;

	}

	double K  = modelingOptions.bulkModulus * 1e11;
	double dilVolume = 2e9 * (D11 + D22 + D33) / ((3*K) * (2.86 * 2.86 * 2.86));

	// Correct coordinates of all atoms in immovable shell taking point defect 
	// dilatation volume into account
	for (atomsIterator = atomsDeque.begin(); atomsIterator != atomsDeque.end(); atomsIterator++) {
		Atom* atom = *atomsIterator;
		
		if (!atom->inShell) continue;

		double r = atom->r.getLength();

		double dR = dilVolume / (4 * 3.14 * r * r);
		atom->r *= (1 - (dR / r));
	}

	// Save calculated forces
	saveForces();

	// Set dilatation volume to result and return it
	relaxationResults.dilatationVolume = dilVolume;
	return relaxationResults;
}

/**
 * Find a relaxed configuration of a given crystallite
 */
RelaxationResults Relaxation::relaxLattice(LPVOID pParam) 
{
	// Prepare some initial variables
	RelaxationResults relaxationResults;
	DWORD relaxationStart = GetTickCount();
	std::deque<Atom*>::iterator atomsIterator;
	CSingleLock lock(&m_Doc->m_CS);

	double kineticE = 0.0;
	double prevKineticE = 0.0;

	double delt = modelingOptions.startDelt;
	int numDempth = 0;
	int lastDempthingStep = 0;
	double modelTime = 0.0;

	lattice->calculateAtomNeighbours(modelingOptions.maximumActionDistance); // Build neighbour table
	
	double startPotE = calculatePotentialEnergy(); // Calculating initial potential energy

	// Execute modelling loop
	for (int step = 0; step < modelingOptions.maximumNumberOfSteps; step++) {
		
		lock.Lock(); // take synchronize lock

		modelTime += delt; // increase physical time

		calculateForces(); // calculate forces acting on atoms in model

		kineticE = integrateVelocities(delt); // Change atoms position, q vectors and calculate qinetic energy

		// Dempthing
		if (modelingOptions.dampingEnabled) {
			if ((step - lastDempthingStep > 5) && (kineticE < prevKineticE)) {

				numDempth++; // increase number of demphings
				delt+=modelingOptions.ddelt; // increase delta time

				dampModel();

				lastDempthingStep = step; // save step when damping was done
				
			}
		}

		prevKineticE = kineticE; // save kinetic energy on this step; required for demphing

		lock.Unlock(); // unlock critical section

		// Maximum number of dampings condition
		if (numDempth > modelingOptions.maximumNumberOfDemphings) break;

		// Maximum delta time condition
		if (delt >= modelingOptions.maxdelt) break;

		// Update view of the model
		if ((step % 5) == 0) {
			m_Doc->UpdateAllViews(NULL);
		}

	} // eo steps cycle


	// Calculate some result values, set them to relaxationResults variable and return it

	double finalPotE = calculatePotentialEnergy();

	if (!modelingOptions.dampingEnabled) {
		finalPotE += kineticE;
	}

	DWORD relaxationEnd = GetTickCount();
	DWORD relaxationElapsed = relaxationEnd - relaxationStart;

	relaxationResults.complexEnergyBeforeRelaxation = startPotE / 160.219;
	relaxationResults.complexEnergyAfterRelaxation = finalPotE / 160.219;
	relaxationResults.complexEnergyAfterRelaxationCorrected = relaxationResults.complexEnergyAfterRelaxation;
	relaxationResults.relaxationEnergy = (startPotE - finalPotE) / 160.219;
	relaxationResults.modelTime = modelTime;

	relaxationResults.numberOfStemps = step;
	relaxationResults.numberOfDempthings = numDempth;

	relaxationResults.calculationTime = relaxationElapsed;

	return relaxationResults;
}

/**
 * Damps the model - recuilds atom nethgbour tables, rollback atom coordinates,
 * and sets to zero all Qi vectors
 */
void Relaxation::dampModel()
{
	lattice->calculateAtomNeighbours(modelingOptions.maximumActionDistance); // Rebuild neighbours table

	std::deque<Atom*>::iterator atomsIterator;
				
	// Set to zero Qi vectors and rollback one step atoms coordinates
	for (atomsIterator = atomsDeque.begin(); atomsIterator != atomsDeque.end(); atomsIterator++) {
		Atom* atom = *atomsIterator;
		if (!atom->moveable) continue;
		atom->q1 = Vector(0,0,0);
		atom->q2 = Vector(0,0,0);
		atom->q3 = Vector(0,0,0);
		atom->q4 = Vector(0,0,0);
		atom->q5 = Vector(0,0,0);
		if (atom == m_Doc->modelingProject->migratingAtom) continue;
		atom->r = atom->rSaved;
	}
}

/**
 * Calculates new atom positions from the forces they're experiencing
 *
 * For integrating we use Nordseick method
 *
 * Returns complex kinetic energy
 */
double Relaxation::integrateVelocities(double delt) 
{
	static const double  c0 = 3.0 / 16.0;
	static const double  c1 = 25.0 / 360.0;
	static const double  c3 = 11.0 / 18.0;
	static const double  c4 = 1.0 / 6.0;
	static const double  c5 = 1.0 / 60.0;

	double kineticE = 0.0;
	for (std::deque<Atom*>::iterator atomsIterator = atomsDeque.begin(); atomsIterator != atomsDeque.end(); atomsIterator++) {
		Atom* atom = *atomsIterator;
		
		if (!atom->moveable) continue; // Don't move immovable atoms
		if (atom == m_Doc->modelingProject->migratingAtom) continue; // Don't move migrating atom

		atom->rSaved = atom->r; // Save current atom position

		atom->r += atom->q1 + atom->q2 + atom->q3 + atom->q4 + atom->q5;
		atom->q1  += 2.0 * atom->q2 + 3.0 * atom->q3+ 4.0 * atom->q4 + 5.0 * atom->q5;
		atom->q2  += 3.0 * atom->q3 + 6.0 * atom->q4 + 10.0 * atom->q5;
		atom->q3  += 4.0 * atom->q4 + 10.0 * atom->q5;
		atom->q4  += 5.0 * atom->q5;
		
		double g = 0.5 * delt * delt / atom->atomType->mass;
		Vector p = g * atom->v - atom->q2;

		atom->r += c0 * p;
		atom->q1 += c1 * p;
		atom->q2 += p;
		atom->q3 += c3 * p;
		atom->q4 += c4 * p;
		atom->q5 += c5 * p;

		kineticE += atom->q1.getLength() * 0.25 / g;

		atom->v = Vector(0,0,0);
	}
	return kineticE;
}

/**
 * For all atoms in model this method saves their forces to vSaved property
 */
void Relaxation::saveForces()
{
	for (std::deque<Atom*>::iterator atomsIterator = atomsDeque.begin(); atomsIterator != atomsDeque.end(); atomsIterator++) {
		Atom* atom = *atomsIterator;

		if (atom->moveable) continue;

		atom->vSaved = atom->v;
	}
}

/**
 * Resets forces of all atoms in model to 0
 */
void Relaxation::resetShellForces()
{
	for (std::deque<Atom*>::iterator atomsIterator = atomsDeque.begin(); atomsIterator != atomsDeque.end(); atomsIterator++) {
		Atom* atom = *atomsIterator;
		if (!atom->moveable) {
			atom->v = Vector();
		}
	}
}

/**
 * Calculates forces that are atoms in model experiencing
 *
 * If we use embedded atom method, forces are calculated as energy gradient - each atom is shifted by dR 
 * in 3 directions, and energy is calculated for all these 4 positions. Deriviatives are calculated as dE/dR
 *
 * In case of pairwise potentials, this function uses energy distribution loaded from file
 */
void Relaxation::calculateForces(bool includeImmoveableAtoms)
{
	for (std::deque<Atom*>::iterator atomsIterator = atomsDeque.begin(); atomsIterator != atomsDeque.end(); atomsIterator++) {
		Atom* atomI = *atomsIterator;
		
		if (!includeImmoveableAtoms && !atomI->moveable) continue;

		if (modelingOptions.useEmbeddedAtomMethod) {
			// Embedded atom method
			
			Vector dPot;
			
			// Calculate energy in given position
			double decPot = calculatePotentialEnergyPerAtom(atomI);

			for (int k = 0; k < 3; k++) {
				atomI->r.coordinate[k] += modelingOptions.diffStep; // Shift atom by modelingOptions.diffStep in all three directions

				double incPot = calculatePotentialEnergyPerAtom(atomI); // Calculate atom energy in shifted position

				dPot.coordinate[k] = (incPot - decPot) / modelingOptions.diffStep; // Calculate gradient coordinate
				
				atomI->r.coordinate[k] -= modelingOptions.diffStep; // Put atom back
			}
			
			atomI->v -= dPot;
		} else {
			// Pairwise potentials case
			std::vector<Atom*>::iterator neigboursAtomsIterator;
			for (neigboursAtomsIterator = atomI->neigbours.begin(); neigboursAtomsIterator != atomI->neigbours.end(); neigboursAtomsIterator++) {
				Atom* atomJ = *neigboursAtomsIterator;
				
				Potential* pot = getPotential(atomI->atomType,atomJ->atomType); // Get potential describing atom types pair

				Vector diff = atomI->r - atomJ->r;
				double r = diff.getLength(); // Calculate the distance between atoms

				// Calculate forces using distribution set by potential
				double qinEnergy = pot->forceDistribution(r); 
                diff *= 0.5 * qinEnergy / r;

                atomI->v += diff;
			}
		}
		
	}
}

/**
 * Calculates and returns the complex energy of the whole crystallite
 */
double Relaxation::calculatePotentialEnergy(bool includeImmoveableAtoms)
{
	double potE = 0.0;
	for (std::deque<Atom*>::iterator atomsIterator = atomsDeque.begin(); atomsIterator != atomsDeque.end(); atomsIterator++) {
		Atom* atomI = *atomsIterator;
		
		if (atomI->inShell) continue;

		double atomPotEnergy = calculatePotentialEnergyPerAtom(atomI);
		potE += atomPotEnergy;
	}
	return potE;
}

/**
 * Calculates and returns the energy per given atom
 */
double Relaxation::calculatePotentialEnergyPerAtom(Atom* atomI)
{
	std::vector<Atom*>::iterator neigboursAtomsIterator;
	double atomPotEnergy = 0.0;

	for (neigboursAtomsIterator = atomI->neigbours.begin(); neigboursAtomsIterator != atomI->neigbours.end(); neigboursAtomsIterator++) {
		Atom* atomJ = *neigboursAtomsIterator;
		Potential* pot = getPotential(atomI->atomType,atomJ->atomType);

		Vector diff = atomI->r - atomJ->r;
		double r = diff.getLength();

		atomPotEnergy += pot->energyDistribution(r) / 2;
	}

	if (modelingOptions.useEmbeddedAtomMethod) {
		double f = 0.0;
		for (neigboursAtomsIterator = atomI->neigbours.begin(); neigboursAtomsIterator != atomI->neigbours.end(); neigboursAtomsIterator++) {
			Atom* atomJ = *neigboursAtomsIterator;

			Vector diff = atomI->r - atomJ->r;
			double r = diff.getLength();

			Potential* pot = getPotential(atomI->atomType,atomJ->atomType);
			f += pot->electronicDensityDistribution(r);
		}
		atomPotEnergy += atomI->atomType->embeddingEnergy(f) * 160.219;
	}

	return atomPotEnergy;
}

Potential* Relaxation::getPotential(AtomType* atomType1, AtomType* atomType2) 
{
	Potential* pot;
	pot = m_Doc->modelingProject->potentials[std::pair<AtomType*,AtomType*>(atomType1,atomType2)];
	
	if (NULL == pot) {
		pot = m_Doc->modelingProject->potentials[std::pair<AtomType*,AtomType*>(atomType2,atomType1)];
	}

	if (NULL == pot) {
		throw PotentialNotLoadedException(atomType1,atomType2);
	}

	return pot;
}