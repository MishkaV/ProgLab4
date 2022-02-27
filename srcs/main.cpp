/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:06:47 by jbenjy            #+#    #+#             */
/*   Updated: 2022/02/27 22:08:36 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lab.hpp"

static void	print_set(std::set<int> some_set, std::string name)
{
	std::cout << "Set " << name << ": ";
	for (std::set<int>::iterator it = some_set.begin(); it != some_set.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n";
}

static void	print_set_nm(std::set<int> some_set,  std::string name)
{
	int a;
	int b;
	
	std::cout << "Input n and m (edges of indexes) of set " << name << "(size from 0 to " << some_set.size() - 1 << ")\n";
	std::cout << "Right = ";
	std::cin >> a;
	std::cout << "Left = ";
	std::cin >> b;

	if (a < 0 || b < 0 || a >= b || b > (int)some_set.size())
	{
		std::cout << "BAD RANGE!!";
		exit(1);
	}

	std::set<int>::iterator it = some_set.begin();
	for (int i = 1; i <= a && it != some_set.end(); i++, it++);
	std::cout << "Set " << name << ": ";
	for (int i = a; i <= b && it != some_set.end(); i++, it++)
		std::cout << *it << " ";
	std::cout << "\n";
}

static std::set<int>	input_universal_set()
{
	std::set<int> U;
	int N;

	std::cout << "Input number of elments in universal set: ";
	std::cin >> N;

	std::cout << "Input universal set: ";
	for (int i = 0, curr = 0; i < N; i++)
	{
		std::cin >> curr;
		U.insert(curr);
	}
	
	return (U);
}	

static std::set<int>	create_set_a(std::set<int> U)
{
	int a;
	int b;
	int N;
	std::set<int> A;


	std::cout << "Input max number of elments in A set: ";
	std::cin >> N;
	
	std::cout << "Input left and right edges of random indexes\n";
	std::cout << "Right = ";
	std::cin >> a;
	std::cout << "Left = ";
	std::cin >> b;

	if (a < 0 || b < 0 || a >= b || b > (int)U.size())
	{
		std::cout << "BAD RANGE!!";
		exit(1);
	}

	
	for (int i = 0; i < N; i++)
	{
		std::set<int>::iterator it = U.begin();
		int rand_ind = rand() % (b - a) + a;
		for (int j = 0; j < rand_ind && it != U.end(); j++, it++);

		if (it != U.end())
			A.insert(*it);
	}

	return (A);
}

static std::set<int>	create_set_b(std::set<int> U)
{
	std::set<int> B;

	for (std::set<int>::iterator it = U.begin(); it != U.end(); it++)
		if (*it % 2)
			B.insert(*it);

	return (B);
}

static void	first_transformations(std::set<int> A, std::set<int> B)
{
	//A ^ B
	std::vector<int> intersect;
	std::set_intersection(A.begin(), A.end(), B.begin(), B.end(), std::back_inserter(intersect));
	
	std::cout << "\nFirst transformations( A ^ B ): \n";
	for (std::vector<int>::iterator it = intersect.begin(); it != intersect.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n";
}

static void	second_transformations(std::set<int> A, std::set<int> B, std::set<int> U)
{
	// /(/A ^ /B)
	std::vector<int> not_a;
	std::set_difference(U.begin(), U.end(), A.begin(), A.end(), std::back_inserter(not_a));

	std::vector<int> not_b;
	std::set_difference(U.begin(), U.end(), B.begin(), B.end(), std::back_inserter(not_b));
	
	std::vector<int> unions;
	std::set_union(not_a.begin(), not_a.end(), not_b.begin(), not_b.end(), std::back_inserter(unions));

	std::vector<int> not_unions;
	std::set_difference(U.begin(), U.end(), unions.begin(), unions.end(), std::back_inserter(not_unions));
	
	std::cout << "Second transformations( /(/A ^ /B) ): \n";
	for (std::vector<int>::iterator it = not_unions.begin(); it != not_unions.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n";
}

int main ()
{
	srand(time(0));
	
	//Task №1
	std::set<int> U = input_universal_set();
	print_set(U, "U");
	
	// Task №2
	std::set<int> A = create_set_a(U);
	print_set(A, "A");
	
	//Task №3
	std::set<int> B = create_set_b(U);
	print_set(B, "B");

	std::vector<int> check_intersect;
	std::set_intersection(A.begin(), A.end(), B.begin(), B.end(), std::back_inserter(check_intersect));

	std::vector<int> check_equal;
	std::set_difference(A.begin(), A.end(), B.begin(), B.end(), std::back_inserter(check_equal));
	
	if (!check_intersect.size() || !check_equal.size())
	{
		std::cout << "Sets A and B give empty intersection or they are equal";
		exit(1);
	}

	//Task №4
	first_transformations(A, B);
	second_transformations(A, B, U);
	
	//Task №5
	print_set_nm(A, "A");
	print_set_nm(B, "B");
	print_set_nm(U, "U");
	

	return (0);
}