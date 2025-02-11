#include <cassert>
#include <cstdlib>
#include <iostream>

#include "leveldb/db.h"
#include "leveldb/write_batch.h"

int main() {
  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;

  leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdba", &db);
  if (status.ok()) {
    printf("/tmp/testdb open successfully!\n");
  }
  else {
    printf("/tmp/testdb open failed!\n");
  }

  std::string key1 = "key005";
  std::string key2 = "key008";
  std::string key3 = "key0007";
  std::string key4 = "keyxx";
  std::string write_val = "bytedance";
  status = db->Put(leveldb::WriteOptions(), key1, write_val);
  status = db->Put(leveldb::WriteOptions(), key2, write_val);
  status = db->Put(leveldb::WriteOptions(), key3, write_val);
  status = db->Put(leveldb::WriteOptions(), key4, write_val);
  status = db->Put(leveldb::WriteOptions(), key4, "new val");
  if (!status.ok()) printf("Put key1 failed");

  leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
  for (it->SeekToFirst(); it->Valid(); it->Next()) {
    std::cout << it->key().ToString() << ": " << it->value().ToString() << std::endl;
  }
  assert(it->status().ok());  // Check for any errors found during the scan
  delete it;

  // std::string res_val;
  // status = db->Get(leveldb::ReadOptions(), key1, &res_val);
  // if (status.ok()) {
  //   std::cout << "Get Key: " << key1 << ", val: " << res_val << std::endl;
  // }

  // // WriteBatch, 原子写入
  // status = db->Get(leveldb::ReadOptions(), key1, &res_val);
  // std::string key2 = "Veeupup";
  // if (status.ok()) {
  //   leveldb::WriteBatch batch;
  //   batch.Delete(key1);
  //   batch.Put(key2, write_val);
  //   status = db->Write(leveldb::WriteOptions(), &batch);
  // }

  // // sync, 开启同步写, 同步写的速度通常比异步写的速度慢 1000 倍
  // leveldb::WriteOptions write_options;
  // write_options.sync = true;
  // db->Put(write_options, "prefix_" + key2, write_val);

  // leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
  // for (it->SeekToFirst(); it->Valid(); it->Next()) {
  //   std::cout << it->key().ToString() << ": " << it->value().ToString()
  //             << std::endl;
  // }



  delete db;  // RAII, delete 的时候会调用DB析构函数自动清理
  return 0;
}
