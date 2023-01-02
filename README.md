# Simple Security System

## States and Inputs
This simple FSM contains 3 states:
- armed
- disarmed
- triggered

And requires 2 inputs:
- door open (door is not locked)
- motion detected


## How it Works
The alarm is disarmed by default, therefore its initial state is 'disarmed'. Take a look at the diagram below showing how the machine works.

```mermaid
graph LR;
A[Start] --> B[disarmed];
B --> C[disarmed] doorOpen=0, motionDetected=0;
B --> D[armed] doorOpen=1, motionDetected=0;
B --> D[armed] doorOpen=0, motionDetected=1;
B --> D[armed] doorOpen=1, motionDetected=1;
D --> E[armed] doorOpen=0, motionDetected=0;
D --> F[triggered] doorOpen=1, motionDetected=0;
D --> F[triggered] doorOpen=0, motionDetected=1;
D --> F[triggered] doorOpen=1, motionDetected=1;
F --> G[triggered] doorOpen=0, motionDetected=0;
F --> G[triggered] doorOpen=1, motionDetected=0;
F --> G[triggered] doorOpen=0, motionDetected=1;
F --> G[triggered] doorOpen=1, motionDetected=1;
C --> B;
G --> D;
E --> D;

```

Below is a state and transition table derived from the diagram above.

| Current State | Input: Door Open | Input: Motion Detected | Next State |
| --- | --- | --- | --- |
| disarmed | 0 | 0 | disarmed |
| disarmed | 1 | 0 | armed |
| disarmed | 0 | 1 | armed |
| disarmed | 1 | 1 | armed |
| armed | 0 | 0 | disarmed |
| armed | 1 | 0 | armed |
| armed | 0 | 1 | triggered |
| armed | 1 | 1 | triggered |
| triggered | 0 | 0 | armed |
| triggered | 1 | 0 | triggered |
| triggered | 0 | 1 | triggered |
| triggered | 1 | 1 | triggered |

graph LR;
A[Start] --> B[disarmed];
B --> C[disarmed] 0,0;
B --> D[armed] 1,0;
B --> D[armed] 0,1;
B --> D[armed] 1,1;
D --> E[armed] 0,0;
D --> F[triggered] 1,0;
D --> F[triggered] 0,1;
D --> F[triggered] 1,1;
F --> G[triggered] 0,0;
F --> G[triggered] 1,0;
F --> G[triggered] 0,1;
F --> G[triggered] 1,1;
C --> B;
G --> D;
E --> D;

## K-Map
TBC


## Truth Table
TBC
