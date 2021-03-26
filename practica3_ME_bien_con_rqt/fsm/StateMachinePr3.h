/*********************************************************************
*  Software License Agreement (BSD License)
*
*   Copyright (c) 2018, Intelligent Robotics
*   All rights reserved.
*
*   Redistribution and use in source and binary forms, with or without
*   modification, are permitted provided that the following conditions
*   are met:

*    * Redistributions of source code must retain the above copyright
*      notice, this list of conditions and the following disclaimer.
*    * Redistributions in binary form must reproduce the above
*      copyright notice, this list of conditions and the following
*      disclaimer in the documentation and/or other materials provided
*      with the distribution.
*    * Neither the name of Intelligent Robotics nor the names of its
*      contributors may be used to endorse or promote products derived
*      from this software without specific prior written permission.

*   THIS SOFTWARE IS PROVStateMachinePr3ED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*   FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*   COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*   INCStateMachinePr3ENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*   BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*   POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

/* Author: Francisco Martín fmrico@gmail.com */

/* Mantainer: Francisco Martín fmrico@gmail.com */
#ifndef STATEMACHINEPR3_H_
#define STATEMACHINEPR3_H_

#include <bica/Component.h>
#include <ros/ros.h>

#include <std_msgs/String.h>

#include <string>

#define CHANGE_TIME 30.0

namespace bica
{
class StateMachinePr3 : public bica::Component
{
public:
  StateMachinePr3();
  virtual ~StateMachinePr3();

  void activateCode();

  	virtual void ball_code_iterative() {};
	virtual void ball_code_once() {};
	virtual void yellow_code_iterative() {};
	virtual void yellow_code_once() {};
	virtual void turn_code_iterative() {};
	virtual void turn_code_once() {};
	virtual void blue_code_iterative() {};
	virtual void blue_code_once() {};

  	virtual bool yellow_2_turn();
	virtual bool blue_2_yellow();
	virtual bool turn_2_ball();
	virtual bool ball_2_blue();


  bool ok();

protected:
  ros::Time state_ts_;

private:
  void step() {}

  	void deactivateAllDeps();
	void ball_activateDeps();
	void yellow_activateDeps();
	void turn_activateDeps();
	void blue_activateDeps();


  	static const int BALL = 0;
	static const int YELLOW = 1;
	static const int TURN = 2;
	static const int BLUE = 3;


  int state_;

  std::string myBaseId_;
  ros::NodeHandle nh_;
  ros::Publisher state_pub_;
};

} /* namespace bica */

#endif /* STATEMACHINEPR3_H_ */
