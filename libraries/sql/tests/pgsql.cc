
#include "symbols.hh"
#include <cassert>
#include <iostream>
#include <lithium.hh>
#include "generic_sql_tests.hh"

int main() {
  using namespace li;

  auto database = pgsql_database(s::host = "localhost", s::database = "postgres", s::user = "postgres",
                          s::password = "lithium_test", s::port = 32768, s::charset = "utf8");

  generic_sql_tests(database);
}
