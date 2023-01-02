#include <stdio.h>
#include <windows.h>

int main() {
  int state = 0; // 0 = disarmed, 1 = armed, 2 = triggered
  int doorOpen = 0; // 0 = locked, 1 = open
  int motionDetected = 0; // 0 = no motion, 1 = motion detected
  int initialState = 0; // initial state (0 = disarmed, 1 = armed)

  // set initial state
  if(initialState == 0) {
    state = 0;
  }

  // loop indefinitely
  while(1) {
    // check for input
    printf("Enter door open status (0 or 1): ");
    scanf("%d", &doorOpen);
    printf("Enter motion detected status (0 or 1): ");
    scanf("%d", &motionDetected);

    // update state based on inputs
    if(state == 0) { // disarmed
      if(doorOpen == 0) {
        state = 0; // system remains disarmed as long as the door is locked
      } else {
        state = 1; // arm system if door is open and/or motion is detected
      }
    } else if(state == 1) { // armed
      if(doorOpen == 0 && motionDetected == 0) {
        state = 0; // disarm system if door is locked and no motion is detected
      } else if(doorOpen == 1 && motionDetected == 0) {
        state = 1; // arm system if door is open
      }
      else {
        state = 2; // trigger alarm if motion is detected
      }
    } else if(state == 2) { // triggered
      if(doorOpen == 0 && motionDetected == 0) {
        state = 1; // reset alarm if door is locked and no motion is detected
      } else {
        state = 2; // alarm keeps on ringing until the door is locked and no motion is detected
      } 
    }


    // print current state
    if(state == 0) {
    printf("==SYSTEM: DISARMED==\n");
    printf("ㅤ\n");
    } else if(state == 1) {
    printf("==SYSTEM: ARMED==\n");
    printf("ㅤ\n");
    } else if(state == 2) {
    printf("==ALARM TRIGGERED==\n");
    printf("ㅤ\n");
    }
  }

  return 0;
}
