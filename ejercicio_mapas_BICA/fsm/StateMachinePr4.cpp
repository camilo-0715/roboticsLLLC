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
*   THIS SOFTWARE IS PROVStateMachinePr4ED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*   FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*   COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*   INCStateMachinePr4ENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*   BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*   POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

/* Author: Francisco Martín fmrico@gmail.com */

/* Mantainer: Francisco Martín fmrico@gmail.com */

#include "StateMachinePr4.h"

namespace bica
{
StateMachinePr4::StateMachinePr4() : state_(BEDROOM), myBaseId_("StateMachinePr4")
{
  state_ts_ = ros::Time::now();
  state_pub_ = nh_.advertise<std_msgs::String>("/" + myBaseId_ + "/state", 1, false);
}

StateMachinePr4::~StateMachinePr4()
{
}

void StateMachinePr4::activateCode()
{
  deactivateAllDeps();

	state_ = BEDROOM;
	state_ts_ = ros::Time::now();

	bedroom_activateDeps();
	bedroom_code_once();
}

bool StateMachinePr4::ok()
{
  if (active_)
  {
    std_msgs::String msg;

    switch (state_)
    {
		case BEDROOM:

			bedroom_code_iterative();

			msg.data = "bedroom";
			ROS_INFO("BEDROOM"); 
			if(bedroom_2_emptyroom())
			{
				ROS_INFO("BEDROOM->EMPTYROOM");
				deactivateAllDeps();

				state_ = EMPTYROOM;
				state_ts_ = ros::Time::now();

				emptyroom_activateDeps();
				emptyroom_code_once();
			}
			state_pub_.publish(msg);
			break;

		case EMPTYROOM:

			emptyroom_code_iterative();

			msg.data = "emptyroom";
			ROS_INFO("EMPTYROOM"); 
			if(emptyroom_2_gym())
			{
				ROS_INFO("EMPTYROOM->GYM");
				deactivateAllDeps();

				state_ = GYM;
				state_ts_ = ros::Time::now();

				gym_activateDeps();
				gym_code_once();
			}
			state_pub_.publish(msg);
			break;

		case GYM:

			gym_code_iterative();

			msg.data = "gym";
			ROS_INFO("GYM"); 
			if(gym_2_kitchen())
			{
				ROS_INFO("GYM->KITCHEN"); 
				deactivateAllDeps();

				state_ = KITCHEN;
				state_ts_ = ros::Time::now();

				kitchen_activateDeps();
				kitchen_code_once();
			}

			state_pub_.publish(msg);
			break;

		case KITCHEN:
			kitchen_code_iterative();

			msg.data = "kitchen";
			ROS_INFO("KITCHEN"); 
			if(kitchen_2_bedroom())
			{
				ROS_INFO("KITCHEN->BEDROOM");
				deactivateAllDeps();

				state_ = BEDROOM;
				state_ts_ = ros::Time::now();

				bedroom_activateDeps();
				bedroom_code_once();
			}
			state_pub_.publish(msg);
			break;
		}
  }

  return Component::ok();
}

void
StateMachinePr4::deactivateAllDeps()
{
	removeDependency("emptyroom");
	removeDependency("bedroom");
	removeDependency("kitchen");
	removeDependency("gym");
};

void
StateMachinePr4::bedroom_activateDeps()
{
	addDependency("bedroom");
}

void
StateMachinePr4::gym_activateDeps()
{
	addDependency("gym");
}

void
StateMachinePr4::kitchen_activateDeps()
{
	addDependency("kitchen");
}

void
StateMachinePr4::emptyroom_activateDeps()
{
	addDependency("emptyroom");
}

} /* namespace bica */