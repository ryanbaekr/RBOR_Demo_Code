/*
 * Sketch     Crawl function example
 * Platform   Ryan Baker Octopod Robot (Arduino/Genuino Mega 2560)
 * Brief      This sketch is used to show how to control Ryan Baker Octopod Robot with code.
 *            You can easily achieve custom function by using RBOR library we provide.
 * Note       Keep the power off when uploading the code to prevent the robot from suddenly moving 
 *            after the upload is complete. Before turning on the power, disconnect the USB cable 
 *            and place the robot on a smooth surface that has no other objects.
 * Author     Ethan Pan @ Freenove (support@freenove.com)
 * Date       2018/11/15
 * Copyright  Copyright © Freenove (http://www.freenove.com)
 * License    Creative Commons Attribution ShareAlike 3.0
 *            (http://creativecommons.org/licenses/by-sa/3.0/legalcode)
 * -----------------------------------------------------------------------------------------------*/

#ifndef ARDUINO_AVR_MEGA2560
#error Wrong board. Please choose "Arduino/Genuino Mega or Mega 2560"
#endif

// Include RBOR (Ryan Baker Octopod Robot) library
#include <RBOR.h>

RBOR robot;

int i = 0;

void setup() {
  robot.Start();

  delay(500);
}

void loop() {
  if (analogRead(A1) < 300) {
    switch ((int)(i/4)) {
      case 0:
        robot.CrawlForward();
        break;
      case 1:
        robot.CrawlBackward();
        break;
      case 2:
        robot.CrawlLeft();
        break;
      case 3:
        robot.CrawlRight();
        break;
      case 4:
        robot.TurnLeft();
        break;
      case 5:
        robot.TurnRight();
        break;
      default:
        // default
        break;
    }
    
    i-=-1;
  
    if (i == 24) {
      i = 0;
    }
  }
}
