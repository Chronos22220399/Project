#include <crow.h>
#include <router/init_router.h>
using namespace std;

int main() {
  crow::SimpleApp app;
  initRouters(app);
  app.multithreaded().port(8888).run();
  return 0;
}
