li::http_client
===============================

`li::http_client` is an easy to use http client built around
the libcurl library.


# Tutorial

```c++
using namespace li;

// Simple GET request:
auto res = http_get("http://www.google.com");
// returns an object with a status and a body member.
std::cout << res.status << std::endl;
std::cout << res.body << std::endl;

// http_post, http_put, http_delete are also avalable.

// GET and POST Parameters.
auto res = http_post("http://my_api.com/update_test", 
                     s::get_parameters = mmm(s::id = 42), 
                     s::post_parameters = mmm(s::name = "John", s::age = 42));

// Access to headers.
auto res = http_get("http://my_api.com/hello", s::fetch_headers);
// returns an object with a status, body AND headers member.
for (auto pair : res.headers) {
  std::cout << pair.first << ":::" << pair.second  << std::endl;
}
```

# What is the s:: namespace ?

Everything explained here: https://github.com/matt-42/lithium/tree/master/libraries/symbol#lisymbol

# Installation / Supported compilers

Everything explained here: https://github.com/matt-42/lithium#installation


# Authors

Matthieu Garrigues https://github.com/matt-42


# Support the project

If you find this project helpful, please consider donating:
https://www.paypal.me/matthieugarrigues
