#include "proyecto_final/coord_reader.hpp"

namespace proyecto_final
{

CoordReader::CoordReader(std::string n): nh_("~")
{
  setCoord();
}

bool
CoordReader::placeExists(std::string place)
{
  return false;  // Borrar posteriormente
}

void
CoordReader::setCoord()
{
}

} // namespace proyecto_final
