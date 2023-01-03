# Home Security System

## States and Inputs
This simple FSM contains 3 states:
- armed
- disarmed
- triggered

And requires 2 inputs:
- door open
- motion detected


## How it Works
The alarm is disarmed by default, therefore its initial state is 'disarmed'. Take a look at the diagrams below showing how the machine works.

**Input syntax:**<br>
doorOpen,motionDetected<br>

doorOpen = 0       --> Door is locked<br>
doorOpen = 1       --> Door is unlocked/open<br>
motionDetected = 0 --> No motion is detected<br>
motionDetected = 1 --> Motion is detected<br>

```mermaid
sequenceDiagram
  participant disarmed as Disarmed
  participant armed as Armed
  participant triggered as Triggered

  disarmed ->> disarmed: Door Locked, No Motion
  disarmed ->> armed: Door Open
  armed ->> armed: Door Open, Motion Detected
  armed ->> triggered: Door Locked, Motion Detected
  triggered ->> triggered: Door Open, Motion Detected
  triggered ->> armed: Door Locked, No Motion
```

The diagram above can be broken down into the one below:
```mermaid
graph LR;
A[Start] --> B[disarmed];
B -- 0,0 --> C[disarmed];
B -- 1,0 --> D[armed];
B -- 0,1 --> D[armed];
B -- 1,1 --> D[armed];
D -- 0,0 --> B[disarmed];
D -- 1,0 --> E[armed];
D -- 0,1 --> F[triggered];
D -- 1,1 --> F[triggered];
F -- 0,0 --> D[armed];
F -- 1,0 --> G[triggered];
F -- 0,1 --> G[triggered];
F -- 1,1 --> G[triggered];
C --> B;
G --> F;
E --> D;
```
What are the diagrams above saying?
- As long as the door is locked and there is no motion detected, the system will remain disarmed. As such, inputting 0,0 repeatedly won't do anything to arm the system.
- The system arms itself if the door is open and/or motion is detected. In other words, any input other than 0,0 while the system is disarmed, will arm the system.
- The system disarms itself if the door is finally locked and no more motion is detected. Therefore, inputting 0,0 while the system is armed, will disarm the system.
- As long as the door is open after arming the system, the system will remain armed. Meaning that inputting 1,0 while the system is armed, keeps the system armed.
- If motion is detected while the system is armed, the alarm will be triggered. Hence, if the value for motionDetected is 1 while the system is armed, the alarm will trigger.
- The alarm will only stop after the door is relocked and no more motion is detected. This resets the system back from 'triggered' to 'armed'. Thus, this reset can only be initiated if 0,0 is inputted while the system is 'triggered'.

Below is the complete state and transition table derived from the diagram above.

| Present State | Present State | Input | Input | Next State | Next State | Output | Output |
|----|----|---|---|-----|-----|----|----|
| s0 | s1 | d | m | s0' | s1' | o0 | o1 |
| 1  | 0  | 0 | 0 | 1   | 0   | 1  | 0  |
| 1  | 0  | 1 | 0 | 0   | 0   | 0  | 0  |
| 1  | 0  | 1 | 1 | 0   | 0   | 0  | 0  |
| 1  | 0  | 0 | 1 | 0   | 0   | 0  | 0  |
| 0  | 0  | 0 | 0 | 1   | 0   | 1  | 0  |
| 0  | 0  | 1 | 0 | 0   | 0   | 0  | 0  |
| 0  | 0  | 0 | 1 | 1   | 1   | 1  | 1  |
| 0  | 0  | 1 | 1 | 0   | 1   | 0  | 1  |
| 0  | 1  | 0 | 0 | 1   | 0   | 1  | 0  |
| 0  | 1  | 0 | 1 | 1   | 1   | 1  | 1  |
| 0  | 1  | 1 | 0 | 0   | 1   | 0  | 1  |
| 0  | 1  | 1 | 1 | 0   | 1   | 0  | 1  |
| 1  | 1  | 0 | 0 | 1   | 1   | 1  | 1  |
| 1  | 1  | 0 | 1 | 1   | 1   | 1  | 1  |
| 1  | 1  | 1 | 0 | 0   | 1   | 0  | 1  |
| 1  | 1  | 1 | 1 | 0   | 1   | 0  | 1  |

- d and m represent doorOpen and motionDetected, respectively.
- s0 and s1 represent 'system disarmed' and 'alarm triggered', respectively. In s0, a value of 0 means that the system is armed, while a value of 1 means that the system is disarmed. In s1, a value of 0 means that the alarm is inactive, while a value of 1 means that the alarm is triggered. The same applies for s0' and s1' respectively.

From this table, we can derive K-maps for the outputs and their respective combinatorial boolean equations. Note that the output is the same as 'Next State', so only two K-Maps will be necessary:

### Next State (s0'):
![s0kmap](images/s0kmap.jpg)

s0' = d

### Next State (s1'):
![s1kmap](images/s1kmap.jpg)

s1' = m + s0s1 + s0d<br>
<br>
Since output is the same as 'Next State':<br>
o0 = s0'<br>
o1 = s1'<br>
Note: Both s0' and s1' in this case represent 'Next State' and are not to be confused with s0 inverted and s1 inverted respectively.

## Implementation in C

### To run the code on Windows in Visual Studio Code (VSC):
1. Download the .c file in my repository and open it on VSC.
2. Set up a debugging configuration for the project by making sure the C/C++ extension and a C compiler (preferably GCC) are installed in VSC. Once it's installed, create a `launch.json` configuration file.
3. Once that's done, you may debug the file and select the configuration which has gcc.exe in it.
4. Once the code is up and running, you may use the terminal to enter your inputs and play around with the FSM.

### Output
Here is an example of the system running:
![systemSS](images/systemSS.PNG)

The images below run the same program as the image above, but the code has now been updated to make the output visualized:
- System disarmed:

![DISARMED](images/DISARMED.PNG)

- System armed:

![ARMED](images/ARMED.PNG)

- Alarm triggered:

![TRIGGERED](images/TRIGGERED.PNG)

