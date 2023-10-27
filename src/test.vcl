vcl 1
import std;
import hiring;

backend localhost {
	.host = "localhost";
	.port = "8080";
}

sub vcl_init {
	std.log("Loaded the hiring VMOD");
}

sub vcl_deliver {
	set resp.http.test = hiring.count("test", "t");
	set resp.http.mississippi = hiring.count("mississippi", "iss");
	set resp.http.hello = hiring.count("hello", "x");
	set resp.http.empty = hiring.count("", "");

	std.log("Test with parameters test and t gave result: " + resp.http.test);
	std.log("Test with parameters mississippi and iss gave result: " + resp.http.mississippi);
	std.log("Test with parameters hello and x gave result: " + resp.http.hello);
	std.log("Test with parameters " + " and " + " gave result: " + resp.http.empty);
}
