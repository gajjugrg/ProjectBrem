# ProjectBrem
-------------------------------------------------------------------
			Project Brem						
-------------------------------------------------------------------
 This project is a simple application of GEANT4 to simulate the 
 bremsstrahlung process of High Energy electron in Carbon. Modified 
 from GEANT4 example B1. 


 1- GEOMETRY DEFINITION

   The geometry is constructed in the Brem::DetectorConstruction class.
   The setup consists of a an envelope of box shape containing a block 
   of carbon.


 2- PHYSICS LIST

   The particle's type and the physic processes which will be available
   in this example are set in the QBBC physics list. This physics list
   requires data files for electromagnetic and hadronic processes.

 3- ACTION INITALIZATION

   Brem::ActionInitialization, instantiates and registers
   to Geant4 kernel all user action classes.

   While in sequential mode the action classes are instatiated just once,
   via invoking the method:
      Brem::ActionInitialization::Build()
   in multi-threading mode the same method is invoked for each thread worker
   and so all user action classes are defined thread-local.

   A run action class is instantiated both thread-local
   and global that's why its instance is created also in the method
      Brem::ActionInitialization::BuildForMaster()
   which is invoked only in multi-threading mode.

 4- PRIMARY GENERATOR

   The primary generator is defined in the Brem::PrimaryGeneratorAction class.
   The default kinematics is a 1 GeV electron, in front of the envelope.

 5- DETECTOR RESPONSE
 
	 The information about the primary electron track is recorded. The kinetic 
	 energy and track length at each step is recored. 

 B- USER INTERFACES

   The user command interface is set via the G4UIExecutive class
   in the main() function in brem.cc


 C- HOW TO RUN
 
    - Execute exampleB1 in the 'interactive mode' with visualization:
        % ./Brem
      and type in the commands from run1.mac line by line:
        Idle> /control/verbose 2
        Idle> /tracking/verbose 1
        Idle> /run/beamOn 10
        Idle> ...
        Idle> exit
      or
        Idle> /control/execute run1.mac
        ....
        Idle> exit

    - Execute exampleB1  in the 'batch' mode from macro files
      (without visualization)
        % ./Brem batch.mac
D- Output

		- The output of the simulation is recorded using G4AnalysisManager 
		and written in a root file named outputBrem.root. 
