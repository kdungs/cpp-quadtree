#include <iostream>
#include <random>
#include <string>

#include "quadtree.h"

void printEntity(const Entity& ent) {
  std::cout << '(' << ent.x() << ',' << ent.y() << ")\n";
}

int main() {
  static const unsigned N = 10000;
  static const double width = 100.0,
                      height = 100.0;
  Quadtree root(width / 2, height / 2, width, height);

  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_real_distribution<double> dist_w(0.0, width),
                                         dist_h(0.0, height);

  for (unsigned i = 0; i < N; i++) {
    root.insert(Entity{dist_w(rng), dist_h(rng)});
  }

  root.traverse([&](const Quadtree &qt, unsigned depth) {
    for (unsigned i = 0; i < depth; i++) {
      std::cout << ' ';
    }
    std::cout << qt.x() << ',' << qt.y() << '\n';
  }, 0);
}