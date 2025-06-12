// Tuples 101

// include libraries
#include <iostream>
#include <tuple>
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <vector>
#include <algorithm>
#include <span>
#include <array>

// Type alias
using Person = std::tuple<std::string, std::string, boost::gregorian::date> ;

// 1.b create function to print elements of person
void PrintPerson (const std::tuple <std::string, std::string, boost::gregorian::date>& p){
    std::cout << "Person details are : " << std::endl;
    std::cout << "Name : " << std::get<0>(p) << std::endl;
    std::cout << "Address : " << std::get<1>(p) << std::endl;
    std::cout << "DoB : " << std::get<2>(p) << std::endl;
    std::cout << "\n";
}

// 1.d sort vector
void sort_vector ( std::vector<Person>& v, int i){

    if (i == 0){
        std::sort(v.begin(), v.end(), [=] (const Person& a , const Person& b) {return std::get<0>(a) < std::get<0>(b);}) ;   
    }
    else if (i == 1){
        std::sort(v.begin(), v.end(), [=] (const Person& a , const Person& b) {return std::get<1>(a) < std::get<1>(b);}) ;
    } else {
        std::sort(v.begin(), v.end(), [=] (const Person& a , const Person& b) {return std::get<2>(a) < std::get<2>(b);}) ;
    }
    
}

// print vector
void print_vector(const std::vector<Person>& vec){
    for (auto v : vec){
        PrintPerson(v);
    }
}

// 1.f print span - range based
template <std::size_t Size = std::dynamic_extent >
void span_print_rangebased (const std::span<Person, Size>& s){
    for (auto i : s){
        PrintPerson(i);
    }
}

// 1.f print span - iterator based
template <std::size_t Size = std::dynamic_extent>
void span_print_iterator (const std::span<Person, Size>& s) {
    for (auto it = s.begin(); it != s.end(); it++){
        PrintPerson(*it) ;
    }
}

// 1.f print span - index based
template <std::size_t Size = std::dynamic_extent>
void span_print_index (const std::span<Person, Size>& s) {
    for (int i = 0; i < s.size(); i++){
        PrintPerson(s[i]) ;
    }
}

// 1.g first N in std::span
template <typename T>
std::span<T> firstN (const std::span <T>& s, std::size_t N){

    std::span<T> firstNspan = std::span<T> (s.begin(), N);

    return firstNspan;
}


// 1.g last N in std::span
template <typename T>
std::span<T> lasttN (const std::span <T>& s, std::size_t N){

    std::span<T> lastNspan = std::span<T> (s.begin() + s.size() - N, N);

    return lastNspan;
}

 

int main() {

    // 1.a - create some instances of Person
    Person p1 = std::make_tuple("John", "765 Kirk Dr, NY", boost::gregorian::date(2002, 02, 21 ) );
    auto p2 = std::make_tuple("Tom", "8767 Hunter Cir, NJ", boost::gregorian::date(2001, 1, 9 ) );
    auto p3 = std::make_tuple("Ron", "9898 Morrison Ave, CO", boost::gregorian::date(1999, 9, 19));
    auto p4 = std::make_tuple("James", "5 St Ave, MI", boost::gregorian::date(1988, 5, 2));
    auto p5 = std::make_tuple("Hannah", "89 Kempner Cir, MN", boost::gregorian::date(1989, 1, 7));


    // 1.b print Person elements
    std::cout << "1.b " << std::endl;
    PrintPerson(p1);
    PrintPerson(p2);
    std::cout << "------------------------------------------------------------";
    std::cout << "\n\n";

    // 1.c create a vector of Person
    std::vector<Person> vec_person = {p1, p2};
    // add to vector
    vec_person.push_back(p3);
    
    // 1.d sort vector based on elecment
    std::cout << "1.d " << std::endl;
    std::cout << "Before Sort" << std::endl;
    print_vector(vec_person);
    sort_vector(vec_person, 2);
    std::cout << "After Sort by DoB" << std::endl;
    print_vector(vec_person);
    std::cout << "------------------------------------------------------------";
    std::cout << "\n\n";
    
    // 1.e Create fixed length and variable legth span views of person
    std::vector<Person> vec_person_sp {p1, p2} ;  // dynamic length 
    std::array<Person, 2> arr_person_sp {p2, p3} ; // static length

    // create span views on vec_person_sp and arr_person_sp
    std::span<Person> span_vec = vec_person_sp;
    std::span<Person, 2> span_arr = arr_person_sp; 

    std::cout << "1.e " << std::endl;
    // print span view
    std::cout << "Span vector print " << std::endl;
    span_print_rangebased(span_vec);
    std::cout << "Span array print " << std::endl;
    span_print_rangebased<2>(span_arr);

    // checking if views are read-only
    span_vec[1] = p3;
    span_arr[1] = p1;

    // print span view after modifying last index
    std::cout << "Span vector print after modify " << std::endl;
    span_print_rangebased(span_vec);
    std::cout << "Span array print after modify " << std::endl;
    span_print_rangebased<2>(span_arr);
    std::cout << "1.e. conclusion : No std::span are not read only" << std::endl;
    std::cout << "------------------------------------------------------------";
    std::cout << "\n\n";
    
    // 1.f  3 types of print statements
    std::cout << "1.f " << std::endl;
    span_print_rangebased(span_vec);
    span_print_iterator<2>(span_arr);
    span_print_index(span_arr);
    std::cout << "------------------------------------------------------------";
    std::cout << "\n\n";

    // 1.g  return first and last elements from a std::span view
    std::vector<Person> vec_person2 {p1, p2, p3, p4, p5};  // create new vector
    std::span<Person> span_vec2 = vec_person2 ;         // new span object
    auto firstN_1 = span_vec2.first<3>() ;        // first N elements using std::span.first
    auto lastN_1 = span_vec2.last<2> () ;         // last N elements using std::span.last

    auto firstN_2 = firstN<Person> (span_vec2, 3);      // create sub space of first N elements
    auto lastN_2 = lasttN<Person> (span_vec2, 2);       // create sub space of last N elements
    
    std::cout << "1.g " << std::endl;
    // first N print (also compare with .first)
    std::cout << "first N using std::span.first" << std::endl;
    span_print_iterator(firstN_1);
    std::cout << "first N using custom firstN" << std::endl;
    span_print_iterator(firstN_2);

    // last N print (also compare with .last)
    std::cout << "last N using std::span.last" << std::endl;
    span_print_iterator(lastN_1);
    std::cout << "last N using custom lastN" << std::endl;
    span_print_iterator(lastN_2);
    std::cout << "------------------------------------------------------------";
    std::cout << "\n\n";

    // 1.h
    // test function std::subspan
    // get Person data at index = 3 and 4
    auto subspan = span_vec2.subspan(2, 2);

    // print
    std::cout << "subspan example :" << std::endl;
    span_print_rangebased(subspan); // print Person at index 2 and index 3 of span_vec2


    return 0;
}