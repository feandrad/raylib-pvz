#pragma once

#include "Entity.h"
#include <algorithm>
#include <unordered_map>
#include <memory>

class EntityPool {
public:
    template<typename T, typename... Args>
    T* CreateEntity(Args&&... args) {
        auto entity = std::make_unique<T>(std::forward<Args>(args)...);
        T* entityPtr = entity.get();
        pool.push_back(std::move(entity));
        return entityPtr;
    }

    void DestroyEntity(Entity* entity) {
        pool.erase(std::remove_if(pool.begin(), pool.end(),
                                  [entity](const std::unique_ptr<Entity>& e) {
                                      return e.get() == entity;
                                  }),
                   pool.end());
    }

private:
    std::vector<std::unique_ptr<Entity>> pool;
};