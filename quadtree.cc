#include "quadtree.h"

void Quadtree::insert(Entity&& entity) {
  if (n_ == MAX_N) {
    double w4 = whalf_ / 2,
           h4 = hhalf_ / 2;
    nw_ = std::unique_ptr<Quadtree>(new Quadtree(x_ - w4, y_ - h4, whalf_, hhalf_));
    ne_ = std::unique_ptr<Quadtree>(new Quadtree(x_ + w4, y_ - h4, whalf_, hhalf_));
    se_ = std::unique_ptr<Quadtree>(new Quadtree(x_ + w4, y_ + h4, whalf_, hhalf_));
    sw_ = std::unique_ptr<Quadtree>(new Quadtree(x_ - w4, y_ + h4, whalf_, hhalf_));
  }
  
  if (n_ >= MAX_N) {
    auto ent = std::move(entity);
    if (ent.y() < y_) {
      if (ent.x() < x_) {
        nw_->insert(std::move(ent));
      } else {
        ne_->insert(std::move(ent));
      }
    } else {
      if (ent.x() < x_) {
        sw_->insert(std::move(ent));
      } else {
        se_->insert(std::move(ent));
      }
    }
  } else {
    entities_[n_] = std::move(entity);
  }

  n_++;
}

Entity* Quadtree::lookup(double x, double y) {
  for (unsigned i = 0; i < n_ && i < MAX_N; i++) {
    if (entities_[i].x() == x && entities_[i].y() == y) {
      return &entities_[i];
    }
  }

  if (n_ <= MAX_N) {
    return nullptr;
  }

  if (y < y_) {
    if (x < x_) {
      return nw_->lookup(x, y);
    } else {
      return ne_->lookup(x, y);
    }
  } else {
    if (x < x_) {
      return sw_->lookup(x, y);
    } else {
      return se_->lookup(x, y);
    }
  }
}

void Quadtree::traverse(std::function<void(const Quadtree&, unsigned)> fn, unsigned depth) {
  fn(*this, depth);
  if (n_ > MAX_N) {
    nw_->traverse(fn, depth + 1);
    ne_->traverse(fn, depth + 1);
    se_->traverse(fn, depth + 1);
    sw_->traverse(fn, depth + 1);
  }
}