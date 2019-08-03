#include <glm/gtc/type_precision.hpp>
#include <glm/gtx/io.hpp>
#include <iostream>
#include <sstream>
#include <typeinfo>

namespace
{
	template <typename CTy, typename CTr>
	std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>& os, glm::precision const& a)
	{
		typename std::basic_ostream<CTy,CTr>::sentry const cerberus(os);

		if (cerberus)
		{
			switch (a) {
			case glm::highp:			os << "uhi"; break;
			case glm::mediump:			os << "umd"; break;
			case glm::lowp:				os << "ulo"; break;
#			if GLM_HAS_ALIGNED_TYPE
				case glm::aligned_highp:	os << "ahi"; break;
				case glm::aligned_mediump:	os << "amd"; break;
				case glm::aligned_lowp:		os << "alo"; break;
#			endif
			}
		}

		return os;
	}

	template <typename U, glm::precision P, typename T, typename CTy, typename CTr>
	std::basic_string<CTy> type_name(std::basic_ostream<CTy,CTr>& os, T const&)
	{
		std::basic_ostringstream<CTy,CTr> ostr;

		if      (typeid(T) == typeid(glm::tquat<U,P>))   { ostr << "quat"; }
		else if (typeid(T) == typeid(glm::tvec2<U,P>))   { ostr << "vec2"; }
		else if (typeid(T) == typeid(glm::tvec3<U,P>))   { ostr << "vec3"; }
		else if (typeid(T) == typeid(glm::tvec4<U,P>))   { ostr << "vec4"; }
		else if (typeid(T) == typeid(glm::tmat2x2<U,P>)) { ostr << "mat2x2"; }
		else if (typeid(T) == typeid(glm::tmat2x3<U,P>)) { ostr << "mat2x3"; }
		else if (typeid(T) == typeid(glm::tmat2x4<U,P>)) { ostr << "mat2x4"; }
		else if (typeid(T) == typeid(glm::tmat3x2<U,P>)) { ostr << "mat3x2"; }
		else if (typeid(T) == typeid(glm::tmat3x3<U,P>)) { ostr << "mat3x3"; }
		else if (typeid(T) == typeid(glm::tmat3x4<U,P>)) { ostr << "mat3x4"; }
		else if (typeid(T) == typeid(glm::tmat4x2<U,P>)) { ostr << "mat4x2"; }
		else if (typeid(T) == typeid(glm::tmat4x3<U,P>)) { ostr << "mat4x3"; }
		else if (typeid(T) == typeid(glm::tmat4x4<U,P>)) { ostr << "mat4x4"; }
		else                                             { ostr << "unknown"; }

		ostr << '<' << typeid(U).name() << ',' << P << '>';

		return ostr.str();
	}
} // namespace {

template <typename T, glm::precision P, typename OS>
int test_io_quat(OS& os)
{
	os << '\n' << typeid(OS).name() << '\n';

	glm::tquat<T,P> const q(1, 0, 0, 0);

	{
		glm::io::basic_format_saver<typename OS::char_type> const iofs(os);

		os << glm::io::precision(2) << glm::io::width(1 + 2 + 1 + 2)
			<< type_name<T,P>(os, q) << ": " << q << '\n';
	}

	{
		glm::io::basic_format_saver<typename OS::char_type> const iofs(os);

		os << glm::io::unformatted
			<< type_name<T,P>(os, q) << ": " << q << '\n';
	}

	return 0;
}

template <typename T, glm::precision P, typename OS>
int test_io_vec(OS& os)
{
	os << '\n' << typeid(OS).name() << '\n';

	glm::tvec2<T,P> const v2(0, 1);
	glm::tvec3<T,P> const v3(2, 3, 4);
	glm::tvec4<T,P> const v4(5, 6, 7, 8);

	os << type_name<T,P>(os, v2) << ": " << v2 << '\n'
		<< type_name<T,P>(os, v3) << ": " << v3 << '\n'
		<< type_name<T,P>(os, v4) << ": " << v4 << '\n';

	glm::io::basic_format_saver<typename OS::char_type> const iofs(os);

	os << glm::io::precision(2) << glm::io::width(1 + 2 + 1 + 2)
		<< type_name<T,P>(os, v2) << ": " << v2 << '\n'
		<< type_name<T,P>(os, v3) << ": " << v3 << '\n'
		<< type_name<T,P>(os, v4) << ": " << v4 << '\n';

	return 0;
}

template <typename T, glm::precision P, typename OS>
int test_io_mat(OS& os, glm::io::order_type otype)
{
	os << '\n' << typeid(OS).name() << '\n';

	glm::tvec2<T,P> const v2_1( 0,  1);
	glm::tvec2<T,P> const v2_2( 2,  3);
	glm::tvec2<T,P> const v2_3( 4,  5);
	glm::tvec2<T,P> const v2_4( 6,  7);
	glm::tvec3<T,P> const v3_1( 8,  9, 10);
	glm::tvec3<T,P> const v3_2(11, 12, 13);
	glm::tvec3<T,P> const v3_3(14, 15, 16);
	glm::tvec3<T,P> const v3_4(17, 18, 19);
	glm::tvec4<T,P> const v4_1(20, 21, 22, 23);
	glm::tvec4<T,P> const v4_2(24, 25, 26, 27);
	glm::tvec4<T,P> const v4_3(28, 29, 30, 31);
	glm::tvec4<T,P> const v4_4(32, 33, 34, 35);

	glm::io::basic_format_saver<typename OS::char_type> const iofs(os);

	os << glm::io::precision(2) << glm::io::width(1 + 2 + 1 + 2)
		<< glm::io::order(otype)
		<< "mat2x2<" << typeid(T).name() << ',' << P << ">: " << glm::tmat2x2<T,P>(v2_1, v2_2) << '\n'
		<< "mat2x3<" << typeid(T).name() << ',' << P << ">: " << glm::tmat2x3<T,P>(v3_1, v3_2) << '\n'
		<< "mat2x4<" << typeid(T).name() << ',' << P << ">: " << glm::tmat2x4<T,P>(v4_1, v4_2) << '\n'
		<< "mat3x2<" << typeid(T).name() << ',' << P << ">: " << glm::tmat3x2<T,P>(v2_1, v2_2, v2_3) << '\n'
		<< "mat3x3<" << typeid(T).name() << ',' << P << ">: " << glm::tmat3x3<T,P>(v3_1, v3_2, v3_3) << '\n'
		<< "mat3x4<" << typeid(T).name() << ',' << P << ">: " << glm::tmat3x4<T,P>(v4_1, v4_2, v4_3) << '\n'
		<< "mat4x2<" << typeid(T).name() << ',' << P << ">: " << glm::tmat4x2<T,P>(v2_1, v2_2, v2_3, v2_4) << '\n'
		<< "mat4x3<" << typeid(T).name() << ',' << P << ">: " << glm::tmat4x3<T,P>(v3_1, v3_2, v3_3, v3_4) << '\n'
		<< "mat4x4<" << typeid(T).name() << ',' << P << ">: " << glm::tmat4x4<T,P>(v4_1, v4_2, v4_3, v4_4) << '\n';

	os << glm::io::unformatted
		<< glm::io::order(otype)
		<< "mat2x2<" << typeid(T).name() << ',' << P << ">: " << glm::tmat2x2<T,P>(v2_1, v2_2) << '\n'
		<< "mat2x3<" << typeid(T).name() << ',' << P << ">: " << glm::tmat2x3<T,P>(v3_1, v3_2) << '\n'
		<< "mat2x4<" << typeid(T).name() << ',' << P << ">: " << glm::tmat2x4<T,P>(v4_1, v4_2) << '\n'
		<< "mat3x2<" << typeid(T).name() << ',' << P << ">: " << glm::tmat3x2<T,P>(v2_1, v2_2, v2_3) << '\n'
		<< "mat3x3<" << typeid(T).name() << ',' << P << ">: " << glm::tmat3x3<T,P>(v3_1, v3_2, v3_3) << '\n'
		<< "mat3x4<" << typeid(T).name() << ',' << P << ">: " << glm::tmat3x4<T,P>(v4_1, v4_2, v4_3) << '\n'
		<< "mat4x2<" << typeid(T).name() << ',' << P << ">: " << glm::tmat4x2<T,P>(v2_1, v2_2, v2_3, v2_4) << '\n'
		<< "mat4x3<" << typeid(T).name() << ',' << P << ">: " << glm::tmat4x3<T,P>(v3_1, v3_2, v3_3, v3_4) << '\n'
		<< "mat4x4<" << typeid(T).name() << ',' << P << ">: " << glm::tmat4x4<T,P>(v4_1, v4_2, v4_3, v4_4) << '\n';
  
	return 0;
}

int main()
{
	int Error(0);

	Error += test_io_quat<float, glm::highp>(std::cout);
	Error += test_io_quat<float, glm::highp>(std::wcout);
	Error += test_io_quat<int, glm::mediump>(std::cout);
	Error += test_io_quat<int, glm::mediump>(std::wcout);
	Error += test_io_quat<glm::uint, glm::lowp>(std::cout);
	Error += test_io_quat<glm::uint, glm::lowp>(std::wcout);

	Error += test_io_vec<float, glm::highp>(std::cout);
	Error += test_io_vec<float, glm::highp>(std::wcout);
	Error += test_io_vec<int, glm::mediump>(std::cout);
	Error += test_io_vec<int, glm::mediump>(std::wcout);
	Error += test_io_vec<glm::uint, glm::lowp>(std::cout);
	Error += test_io_vec<glm::uint, glm::lowp>(std::wcout);

	Error += test_io_mat<float, glm::highp>(std::cout, glm::io::column_major);
	Error += test_io_mat<float, glm::lowp>(std::wcout, glm::io::column_major);
	Error += test_io_mat<float, glm::highp>(std::cout, glm::io::row_major);
        Error += test_io_mat<float, glm::lowp>(std::wcout, glm::io::row_major);

	return Error;
}
