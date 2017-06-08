/*
Copyright (c) 2017, Robert Krook
Copyright (c) 2017, Erik Almblad
Copyright (c) 2017, Hawre Aziz
Copyright (c) 2017, Alexander Branzell
Copyright (c) 2017, Mattias Eriksson
Copyright (c) 2017, Carl Hjerpe
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Chalmers University of Technology nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "ros/ros.h"
#include "mapserver/getMarkPos.h"
#include "mapserver/isFPos.h"
#include "../map.h"

Map g_map;


bool getMarkingPosition(mapserver::getMarkPos::Request &req,
                   mapserver::getMarkPos::Response &res)
{
    int id, x, y = 0;
    id = (int) req.id;
    g_map.getMarkingPos(id,x,y);
    res.x = x;
    res.y = y;
    ROS_INFO("request id: %d", req.id);
    ROS_INFO("markpos: (%d,%d)",res.x, res.y);
    return true;
}

bool isForbiddenPos(mapserver::isFPos::Request &req,
                   mapserver::isFPos::Response &res)
{
    int x = req.x;
    int y = req.y;
    bool b = false;
    g_map.isForbiddenPos(x, y, b);
    res.b = b;
    ROS_INFO("pos(%d,%d)", x, y);
    ROS_INFO("result: %d" + b );
    return true;
}




int main(int argc, char **argv)
{
    ros::init(argc, argv, "mapserver");
    ros::NodeHandle n;

    ros::ServiceServer service1 = n.advertiseService("markingPos", getMarkingPosition);

    ros::ServiceServer service2 = n.advertiseService("forbiddenPos", isForbiddenPos);
   
    ROS_INFO("Ready to serve");
    ros::spin();
    return 0;
}
