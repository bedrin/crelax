CRelax
======
[ ![Download](https://api.bintray.com/packages/bedrin/github/crelax/images/download.svg) ](https://bintray.com/bedrin/github/crelax/_latestVersion)

Modelling point defects in crystal BCC and FCC lattices using pair-wise potentials or embedded atom model

Installing
======

- [LatticeRelaxation.exe](https://github.com/bedrin/crelax/releases/download/1.0.0/LatticeRelaxation.exe)
- [potentials.zip](https://github.com/bedrin/crelax/releases/download/1.0.0/potentials.zip)

CRelax is a single `LatticeRelaxation.exe` file - just download it from [github](https://github.com/bedrin/crelax/releases/download/1.0.0/LatticeRelaxation.exe) or [bintray](https://bintray.com/artifact/download/bedrin/github/LatticeRelaxation.exe) official mirror and execute.
It is tested on Windows XP and Windows 7, but should work on Vista and 8. Both 32-bit and 64-bit systems are supported

You can also download some sample potentials data - there're Johnson pair-wise potential for FeFe and also embedded atom potentials for FeFe and FeP lattices. An archive `potentials.zip` is also availabl both on [github](https://github.com/bedrin/crelax/releases/download/1.0.0/potentials.zip) and [bintray](https://bintray.com/artifact/download/bedrin/github/potentials.zip) official mirror

Usage: vacancy in α-Fe (Johnson potential)
======

Let's calculate the relaxation energy after introducing a vacancy in BCC iron using pair-wise potential

Start CRelax and generate a BCC lattice. Default settings will work:

![Generate Lattice](https://bedrin.github.io/crelax/images/generatelattice.png "Generate Lattice")

Select one atom - it will be highlighted with green; you can see the coordinate (in lattice parameters) in the right bottom corner. Let us select atom (0.5, 0.5, 0.5):

![Selected Atom](https://bedrin.github.io/crelax/images/selectedatom.png "Selected Atom")

Click on (X) icon in toolbar and remove the atom. This is how vacancies are introduced.

Now open potentials dialog using main menu item `Potentials/Select Potential`
And select Johnson potential `jFeFe.pt` for Fe-Fe pair:

![Pair Potential](https://bedrin.github.io/crelax/images/pairpotential.png "Pair Potential")

Click on play icon in Toolbar - observer the atoms are moving until the reach the equilibrium positions.
Once simulation is finished, you'll see a results dialog:

![Relaxation Result](https://bedrin.github.io/crelax/images/relaxationresult.png "Relaxation Result")

You can use your mouse to rotate the lattice, press ALT+Mouse and PageUp/PageDown to move the "camera"
Now you can see that atoms have shifted after relaxation of the lattice with a vacancy:

![Relaxed Lattice With Vacancy](https://bedrin.github.io/crelax/images/relaxedvacancy.png "Relaxed Lattice With Vacancy")
