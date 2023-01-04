#include <stdio.h>

int main() {
  int state = 0; // 0 = disarmed, 1 = armed, 2 = triggered
  int doorOpen = 0; // 0 = locked, 1 = open
  int motionDetected = 0; // 0 = no motion, 1 = motion detected
  int initialState = 0; // initial state (0 = disarmed, 1 = armed)
  int oldState = -1; // variable to store the previous state

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
      if(doorOpen == 0 && motionDetected == 0) {
        state = 0; // system remains disarmed as long as the door is locked
      } else if(doorOpen == 1 || motionDetected == 1){
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


    // print current state if it has changed
    if(state != oldState) {
      oldState = state;
      printf("       :================:\n");
      if (state==0) {
        printf("      /||\033[47m              \033[0m||\n");
        printf("     / ||\033[47m   DISARMED   \033[0m||\n");
        printf("    |  ||\033[47m              \033[0m||\n");
        printf("     \\ ||\033[47m              \033[0m||\n");
      } else if (state==1) {
        printf("      /||\033[42m              \033[0m||\n");
        printf("     / ||\033[42m     ARMED    \033[0m||\n");
        printf("    |  ||\033[42m              \033[0m||\n");
        printf("     \\ ||\033[42m              \033[0m||\n");
      } else if (state==2) {
        printf("      /||\033[41m              \033[0m||\n");
        printf("     / ||\033[41m \033[33m!!\033[37mTRIGGERED\033[33m!!\033[37m\033[0m||\n");
        printf("    |  ||\033[41m              \033[0m||\n");
        printf("     \\ ||\033[41m              \033[0m||\n");
      }
      printf("       ==================\n");
      printf("            /  \033[36m⊞\033[0m  \\\n");
      printf("          ############\n");
    }
  }

  return 0;
}
