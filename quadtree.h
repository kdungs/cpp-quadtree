#pragma once

#include <array>
#include <functional>
#include <memory>
#include <string>

class Entity {
public:
  Entity() = default;
  Entity(double x, double y) : x_(x), y_(y) {}
  double x() const {
    return x_;
  }
  double y() const {
    return y_;
  }
  void setX(double x) {
    x_ = x;
  }
private:
  double x_, y_;
};

class Quadtree {
public:
  static const unsigned MAX_N = 4;
  Quadtree(double x, double y, double width, double height) : x_(x), y_(y), whalf_(width / 2), hhalf_(height / 2), n_(0) {}
  void insert(Entity&&);
  Entity* lookup(double, double);
  void traverse(std::function<void(const Quadtree&, unsigned)> fn, unsigned);
  double x() const {
    return x_;
  }
  double y() const {
    return y_;
  }
private:
  const double x_, y_, whalf_, hhalf_;
  unsigned n_;
  std::array<Entity, MAX_N> entities_;
  std::unique_ptr<Quadtree> nw_, ne_, se_, sw_;
};