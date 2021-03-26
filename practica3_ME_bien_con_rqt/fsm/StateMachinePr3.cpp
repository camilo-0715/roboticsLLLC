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

#include "StateMachinePr3.h"

namespace bica
{
StateMachinePr3::StateMachinePr3() : state_(BALL), myBaseId_("StateMachinePr3")
{
  state_ts_ = ros::Time::now();
  state_pub_ = nh_.advertise<std_msgs::String>("/" + myBaseId_ + "/state", 1, false);
}

StateMachinePr3::~StateMachinePr3()
{
}

void StateMachinePr3::activateCode()
{
  	deactivateAllDeps();

	state_ = BALL;
	state_ts_ = ros::Time::now();

	ball_activateDeps();
	ball_code_once();

}

bool 
StateMachinePr3::yellow_2_turn()
{
  return (ros::Time::now() - state_ts_).toSec() > CHANGE_TIME;
}

bool 
StateMachinePr3::blue_2_yellow()
{
  return (ros::Time::now() - state_ts_).toSec() > CHANGE_TIME;
}

bool 
StateMachinePr3::turn_2_ball()
{
  return (ros::Time::now() - state_ts_).toSec() > CHANGE_TIME;
}

bool 
StateMachinePr3::ball_2_blue()
{
  return (ros::Time::now() - state_ts_).toSec() > CHANGE_TIME;
}

bool StateMachinePr3::ok()
{
  if (active_)
  {
    std_msgs::String msg;

    switch (state_)
    {
      	case BALL:

	ball_code_iterative();

	msg.data = "ball";
	if(ball_2_blue())
	{

	deactivateAllDeps();

	state_ = BLUE;
	state_ts_ = ros::Time::now();

	blue_activateDeps();
	blue_code_once();
	}
	state_pub_.publish(msg);
	break;

	case YELLOW:

	yellow_code_iterative();

	msg.data = "yellow";
	if(yellow_2_turn())
	{

	deactivateAllDeps();

	state_ = TURN;
	state_ts_ = ros::Time::now();

	turn_activateDeps();
	turn_code_once();
	}
	state_pub_.publish(msg);
	break;

	case TURN:

	turn_code_iterative();

	msg.data = "turn";
	if(turn_2_ball())
	{

	deactivateAllDeps();

	state_ = BALL;
	state_ts_ = ros::Time::now();

	ball_activateDeps();
	ball_code_once();
	}
	state_pub_.publish(msg);
	break;

	case BLUE:

	blue_code_iterative();

	msg.data = "blue";
	if(blue_2_yellow())
	{

	deactivateAllDeps();

	state_ = YELLOW;
	state_ts_ = ros::Time::now();

	yellow_activateDeps();
	yellow_code_once();
	}
	state_pub_.publish(msg);
	break;


    }
  }

  return Component::ok();
}

void
StateMachinePr3::deactivateAllDeps()
{
	removeDependency("blue");
	removeDependency("ball");
	removeDependency("turn");
	removeDependency("yellow");
};

void
StateMachinePr3::ball_activateDeps()
{
	addDependency("ball");
}

void
StateMachinePr3::yellow_activateDeps()
{
	addDependency("yellow");
}

void
StateMachinePr3::turn_activateDeps()
{
	addDependency("turn");
}

void
StateMachinePr3::blue_activateDeps()
{
	addDependency("blue");
}



} /* namespace bica */
