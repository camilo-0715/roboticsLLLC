#include "ejercicio_mapas/movement.hpp"
#include "ejercicio_mapas/coord_reader.hpp"
#include <string>
#include <iostream>

void executeNavigation(std::string place)
{
    ejercicio_mapas::CoordReader coord(place);
    ejercicio_mapas::Movement mov;

    double x = coord.getX();
    double y = coord.getY();

    ROS_INFO("target coordinates: (%f, %f)", x, y);
    mov.moveRobot(x,y,1.0);
    return;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "ejercicio_mapas");
    ROS_INFO("origin->bedroom");

    while (true){
        
        executeNavigation("bedroom");

        ROS_INFO("bedroom -> gym");
        executeNavigation("gym");

        ROS_INFO("gym -> empty_room");
        executeNavigation("empty_room");

        ROS_INFO("empty_room -> kitchen");
        executeNavigation("kitchen");

        ROS_INFO("kitchen->bedroom");

    }

    return 0;
}
