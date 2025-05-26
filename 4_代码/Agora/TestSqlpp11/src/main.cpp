#include <chrono.hpp>
#include <fmt/format.h>
#include <iostream>
#include <ratio>
#include <sqlpp11/sqlpp11.h>
#include <thread>

void test_datetime()
{
  using namespace std::chrono;
  auto now = system_clock::now();
  auto t = datetime_to_string(now);
  fmt::println("{}", t);
  fmt::println("{}", now.time_since_epoch().count());
  auto time = string_to_datetime(t);
  fmt::println("{}", time.time_since_epoch().count());
}

void time_cast()
{
  using namespace std::chrono;
  milliseconds ms(1678);
  seconds s = duration_cast<seconds>(ms);
  auto remains = ms - s;

  fmt::println("{}", ms.count());
  fmt::println("{}", s.count());
  fmt::println("{}.{}", s.count(), remains.count());
}

void diff_between_steady_with_system()
{
  using namespace std::chrono;
  auto begin = system_clock::now();
  std::this_thread::sleep_for(seconds(1));
  auto end = system_clock::now();

  auto s_begin = steady_clock::now();
  std::this_thread::sleep_for(seconds(1));
  auto s_end = steady_clock::now();

  fmt::println("{}", duration_cast<milliseconds>(begin - end).count());
  fmt::println("{}", duration_cast<milliseconds>(s_begin - s_end).count());
}

void interact_with_c()
{
  using namespace std::chrono;
  auto now = system_clock::now();
  auto tt = system_clock::to_time_t(now);
}

void test_datetime_1() {}

int main()
{
  using namespace std::chrono;
  using fp_seconds = duration<double, std::ratio<1>>;
  using fp_minutes = duration<double, std::ratio<60>>;
  milliseconds ms = 1678ms;

  fp_minutes m = ms;
  fp_seconds s = ms;
  fmt::println("{}", m.count());
  fmt::println("{}", s.count());

  return 0;
}
