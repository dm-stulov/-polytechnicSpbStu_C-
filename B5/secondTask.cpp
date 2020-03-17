#include "secondTask.hpp"

void secondTask(){
  std::vector < Shape > vector;

  std::transform(std::istream_iterator<Line>(std::cin), std::istream_iterator<Line>(),
                 std::back_inserter(vector), readShapeData);

  const int vertices = countVertices(vector);
  std::cout << "Vertices: " << vertices << "\n";

  const size_t triangles = countTriangles(vector);
  std::cout << "Triangles: " << triangles << "\n";

  const size_t squares = countSquares(vector);
  std::cout << "Squares: " << squares << "\n";

  const size_t rectangles = countRectangles(vector);
  std::cout << "Rectangles: " << rectangles << "\n";

  removePentagon(vector);

  const std::vector< Point > pointVector = createPointVector(vector);
  std::cout << "Points:";
  for (auto it : pointVector) {
    std::cout << " (" << it.x << ";" << it.y << ")";
  }

  auto triangleEnd = std::partition(vector.begin(), vector.end(), isTriangle);
  auto squareEnd = std::partition(triangleEnd, vector.end(), isSquare);
  std::partition(squareEnd, vector.end(), isRectangle);

  std::cout << "\nShapes:\n";
  for (auto &it : vector) {
    std::cout << it.size() ;
    for (auto &sIt : it) {
      std::cout << " (" << sIt.x << ";" << sIt.y << ")";
    }
    std::cout << "\n";
  }

};

Shape readShapeData(const Line &line)
{
  std::stringstream iss(line);

  int vertexCount;
  iss >> vertexCount;

  Shape shape;
  const size_t lineLength = line.length();
  for(int i = 0; i < vertexCount; i++)
  {
    Point point{0, 0};
    iss.ignore(lineLength, '(');
    iss >> point.x;

    iss.ignore(lineLength, ';');
    iss >> point.y;

    iss.ignore(lineLength, ')');
    shape.push_back(point);
  }

  if(iss.fail())
  {
    throw std::invalid_argument("Invalid value of points;\n");
  }

  std::string remLine;
  std::getline(iss, remLine);
  if(std::find_if(remLine.begin(), remLine.end(),
                  [](char c) {return !std::isspace(c, std::locale()); }) != remLine.end())
  {
    throw std::invalid_argument("Invalid input data;\n");
  }
  return shape;
}

int countVertices(const std::vector<Shape> &vector)
{
  const int num = std::accumulate(vector.begin(), vector.end(), 0, []
                  (int verticesNum, const Shape &shape) {
                    return verticesNum + shape.size();
                  });
  return num;
};

size_t countTriangles(const std::vector < Shape > &vector)
{
  return static_cast<size_t >(std::count_if(vector.begin(), vector.end(), isTriangle));
};

size_t countSquares(const std::vector < Shape > &vector)
{
  return static_cast<size_t >(std::count_if(vector.begin(), vector.end(), isSquare));
};

size_t countRectangles(const std::vector < Shape > &vector)
{
  return static_cast<size_t >(std::count_if(vector.begin(), vector.end(), isRectangle));
};

bool isSquare(const Shape &shape)
{
  bool isSquare = false;
  if (shape.size() == 4){

    const int maxX = (std::max_element(shape.begin(), shape.end(), compareX))->x;
    const int minX = (std::min_element(shape.begin(), shape.end(), compareX))->x;

    const int maxY = (std::max_element(shape.begin(), shape.end(), compareY))->y;
    const int minY = (std::min_element(shape.begin(), shape.end(), compareY))->y;

    if ((maxX - minX) == (maxY - minY)){
      isSquare = true;
    }
  }

  return isSquare;
};

bool isRectangle(const Shape &shape)
{
  bool isRectangle = false;
  if (shape.size() == 4) {
    isRectangle = true;
  }
  return isRectangle;
}

bool isTriangle(const Shape &shape){
  return (shape.size() == 3);
}

void removePentagon(std::vector < Shape > &vector)
{
  vector.erase(std::remove_if(vector.begin(), vector.end(), []
               (const Shape &sh){
                 return sh.size() == 5;
               }), vector.end());

}

std::vector< Point > createPointVector(const std::vector < Shape > &vector)
{
  std::vector< Point > pointVector;

  pointVector.reserve(vector.size());
  for (const auto &it : vector) {
    pointVector.push_back(it.at(0));
  }

  return pointVector;
}

bool compareX(const Point &point1, const Point &point2){
  return point1.x < point2.x;
}

bool compareY(const Point &point1, const Point &point2){
  return point1.y < point2.y;
}
