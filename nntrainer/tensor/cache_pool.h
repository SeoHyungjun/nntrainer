// SPDX-License-Identifier: Apache-2.0
/**
 * Copyright (C) 2022 Jiho Chu <jiho.chu@samsung.com>
 *
 * @file   cache_pool.h
 * @date   01 July 2022
 * @see    https://github.com/nnstreamer/nntrainer
 * @author Jiho Chu <jiho.chu@samsung.com>
 * @bug    No known bugs except for NYI items
 * @brief  Cache pool class inherited from memory pool
 *
 */

#ifndef __CACHE_POOL_H__
#define __CACHE_POOL_H__

#include <mutex>
#include <memory_pool.h>
#include <list>
#include <nntrainer_log.h>
#include <swap_device.h>

namespace nntrainer {

/**
 * @class   CacheElem
 * @brief   Cache element containing swap address
 */
class CacheElem {
public:
  /**
   * @brief CacheElem default constructor
   *
   */
  explicit CacheElem(std::shared_ptr<SwapDevice> dev, unsigned int mem_id,
                     int off, size_t len,
                     std::shared_ptr<MemoryData<float>> data,
                     std::vector<unsigned int> order) :
    device(dev),
    active(false),
    id(mem_id),
    offset(off),
    length(len),
    mem_data(data),
    exe_order(order) {}

  /**
   * @brief CacheElem destructor
   *
   */
  virtual ~CacheElem() {}

  /**
   * @brief load data from swap device
   *
   */
  void swapIn();

  /**
   * @brief unload data to swap device
   *
   */
  void swapOut();

  /**
   * @brief unload data to swap device
   *
   * @return active status
''   */
  bool isActive() const { return active; }

  /**
   * @brief get execution orders
   *
   * @return execution orders
   */
  std::vector<unsigned int> &getExeOrder() { return exe_order; }

  /**
   * @brief get length of cache element
   *
   * @return length of cache element in byte
   */
  size_t getLength() const { return length; }


  unsigned int getId() const { return id; }

private:
  std::mutex device_mutex; /**< protect device */
  std::shared_ptr<SwapDevice> device; /**< swap device */
  bool active;                        /**< element is loaded */
  unsigned int id;                    /**< memory id */
  int offset;                         /**< element offset from swap device */
  size_t length;                      /**< element size */
  std::shared_ptr<MemoryData<float>> mem_data; /**< allocated memory data */
  std::vector<unsigned int> exe_order;    /**< execution order */
};

/**
 * @class   CachePool
 * @brief   Cache memory with fixed size utilizing swap device
 */
class CachePool : public MemoryPool {
public:
  /**
   * @brief CachePool default constructor
   *
   */
  explicit CachePool(const std::string &name);

  /**
   * @brief MemoryPool destructor
   *
   */
  virtual ~CachePool();

  /**
   * @brief Do the allocation of cache
   *
   */
  virtual void allocate();

  /**
   * @brief Free all the allocated cache
   *
   */
  virtual void deallocate();

  /**
   * @brief Get the allocated cache
   *
   * @param id The token received from the requestMemory
   *
   * @return The pointer of the cache
   *
   * @details This function will throw if called before allocation.
   */
  virtual std::shared_ptr<MemoryData<float>> getMemory(unsigned int id);

  /**
   * @brief Is the cache pool allocated
   *
   * @return true if the memory is allocated, else false
   */
  virtual bool isAllocated() const;

  /**
   * @brief Flush cache data to device
   *
   */
  virtual void flush();

  /**
   * @brief Flush cache data to device except given order
   *
   * @param order except execution order
   */
  virtual void flushExcept(unsigned int order);

private:
  /**
   * @brief validate cache element
   *
   * @param cache element id
   */
  void validate(unsigned int id);

  /**
   * @brief invalidate cache element
   *
   * @param cache element id
   */
  void invalidate(unsigned int id);

  std::shared_ptr<SwapDevice> swap_device; /**< swap device */
  std::map<unsigned int, std::shared_ptr<CacheElem>>
    elems; /**< cache elements */

  std::list<std::shared_ptr<CacheElem>> actives;
};

} // namespace nntrainer

#endif /** __CACHE_POOL_H__ */