#### 首先修改 `xxx_service.h`
> `xxx` 就是对应的表名，比如 `sales_order` 对应的就是 `sales_order_service.h`

##### 先改上半部分
``` C++
#pragma once
#include <crow.h>
#include <string>

class SalesOrderService {
  public:
  static ServiceResult create({} & dto);
  static ServiceResult update(const std::string& ex_id, {} & dto);
  static ServiceResult remove(const std::string& ex_id);
  static ServiceResult getByPage(const int page, const int page_size);
  static ServiceResult getAll();
};
```

注意，示例的是格式化后的样子，因此排版会整齐一些，但是不会影响运行

##### 首先添加需要的 dto 头文件
例如：
对于 `sales_order` 而言，它属于 `sales` 模块，因此其写法为:
```C++
#include <model/dto/sales/sales_order_dto.hpp>
```
> 可以通过查看 `sales_order.ddl` 在哪个文件夹下查看其对应的模块，`sales_order.ddl` 在 sales 下，则属于 sales 模块

##### 接着改 create 函数
原本:
```C++
  static ServiceResult create({} & dto);
```

更改后：
```C++
  static ServiceResult create(SalesOrderDTO & dto);
```
> 这里的 SalesOrderDTO 就是刚刚改过的那个文件里的结构体


##### 接着改 update 和 remove 函数
原本：
```C++
  static ServiceResult update(const std::string& ex_id, SalesOrderDTO & dto);
  static ServiceResult remove(const std::string& ex_id);
```

需要查看 ddl 是否有 xxx_id （表单名_id），有则将这两个函数加上后缀

对于 update，仍然需要将 `{}` 改为 `XXXDTO`
> 根据对应的表单更改，例如，对于 `sales_order` 需要改成 `SalesOrderDTO`

更改后：
```C++
  static ServiceResult updateBySalesOrderId(const std::string& ex_id, SalesOrderDTO & dto);
  static ServiceResult removeBySalesOrderId(const std::string& ex_id);
```

整体更改后：
```C++
#pragma once
#include <crow.h>
#include <string>
#include <model/dto/sales/sales_order_dto.hpp>

class SalesOrderService {
  public:
  static ServiceResult create(SalesOrderDTO & dto);
  static ServiceResult updateBySalesOrderId(const std::string& ex_id, SalesOrderDTO & dto);
  static ServiceResult removeBySalesOrderId(const std::string& ex_id);
  static ServiceResult getByPage(const int page, const int page_size);
  static ServiceResult getAll();
};
```

这样这个文件就改完了

---

##### 接下来更改 `sales_order_service.cpp`
对于 service 对应的 cpp 文件，采用一样的改法

##### 首先改 `create` 函数
将 `{}` 改为 `SalesOrderDTO`

更改前:
```C++
ServiceResult SalesOrderService::create({} &dto) {
	return {false, "Not implemented yet."};
 }
```

更改后：
```C++
ServiceResult SalesOrderService::create(SalesOrderDTO &dto) {
	return {false, "Not implemented yet."};
 }
```

##### 接着更改 `update` 和 `remove` 函数
两个函数和前面对 .h 头文件的更改方式相同

更改前：
```C++
ServiceResult SalesOrderService::update(const std::string &ex_id, {} &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult SalesOrderService::remove(const std::string &ex_id) {
	return {false, "Not implemented yet."};
 }
```
更改后：
```C++
ServiceResult SalesOrderService::updateBySalesOrderId(const std::string &ex_id, SalesOrderDTO &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult SalesOrderService::removeBySalesOrderId(const std::string &ex_id) {
	return {false, "Not implemented yet."};
 }
```

这样这个文件也改完了