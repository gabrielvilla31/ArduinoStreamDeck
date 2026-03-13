# 🎛️ ArduinoStreamDeck
📌 Overview

This project connects 4 physical buttons to an Arduino board.
When a button is pressed:
1. The Arduino detects the button press.
2. It determines whether the press is short or long.
3. It sends the button identifier and press type through the serial COM port to a PC.
4. A C++ application running on the PC reads the incoming serial data.
5. The application executes an action defined in a configuration XML file.

👉 Currently, the only implemented action is launching a script on the PC.

Additionally, the repository includes a 3D printable enclosure (.stl) designed to house the Arduino and the 4 buttons.

🏗️ Project Architecture
````
[ Buttons ]
     ↓
[ Arduino ]
     ↓ (Serial / COM Port)
[ C++ PC Application ]
     ↓
[ config.xml ]
     ↓
[ Script Execution ]
````
⚙️ XML Configuration

Button actions are defined in the config.xml file.
```
<?xml version="1.0" encoding="utf-8" ?>
<config>
	<node 
		id="Button 1" 
		actionPress="Start Script" argPress="C:\Simulator\script1.bat" 
		actionHold="Start Script" argHold="C:\Simulator\script1H.bat"
	/>
	<node 
		id="Button 2" 
		actionPress="lock" argPress=""
		actionHold="shutdown" argHold=""
	/>
	<node 
		id="Button 3" 
		actionPress="" argPress=""
		actionHold="" argHold=""
	/>
	<node 
		id="Button 4" 
		actionPress="" argPress=""
		actionHold="" argHold=""
	/>
</config>
```
▶️ Currently Supported Action
Action Type	    Description
script	        Launches a script (.bat, .ps1, .exe, etc.)
lock			Locks the screen and stop music.
shutdown		Shutdowns the computer

🖨️ 3D Printable Enclosure
The repository includes a .stl 3D model for a custom enclosure designed to house:
The Arduino board
The 4 push buttons
You can print it using any standard 3D printer (PLA recommended).

🚀 Installation

1️⃣ Arduino

Open the .ino file in the Arduino IDE
Select the correct board and COM port
Upload the firmware

2️⃣ PC Application

Compile the project (Visual Studio recommended for Windows)
Place config.xml in the same directory as the executable

🧪 Quick Test

Start the C++ application
Press one of the buttons
Verify that the corresponding script is executed
