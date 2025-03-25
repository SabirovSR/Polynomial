#include "..\polinom\Monom.h"
#include "..\polinom\Monom.cpp"
#include "..\polinom\Polynomial.h"
#include <string>
#include <string>
#include "gtest.h"

// Проверка создания монома по умолчанию
TEST(Monom, can_create_default_monom) 
{
    ASSERT_NO_THROW(Monom m);
}

// Проверка создания монома с параметрами
TEST(Monom, can_create_monom_with_parameters)
{
    ASSERT_NO_THROW(Monom m(2.5, 3, 1, 2));
}

// Проверка присвоеня параметров монома
TEST(Monom, monom_with_parameters_has_correct_values)
{
    Monom m(2.5, 3, 1, 2);
    EXPECT_DOUBLE_EQ(2.5, m.coeff);
    EXPECT_EQ(3, m.x);
    EXPECT_EQ(1, m.y);
    EXPECT_EQ(2, m.z);
}

// Проверка на присвоение коэфа
TEST(Monom, can_set_coeff) 
{
    Monom m;
    m.SetCoeff(3.5);
    EXPECT_DOUBLE_EQ(3.5, m.coeff);
}

// Проверка установления степеней монома
TEST(Monom, can_set_xyz) 
{
    Monom m;
    m.SetXYZ(1, 2, 3);
    EXPECT_EQ(1, m.x);
    EXPECT_EQ(2, m.y);
    EXPECT_EQ(3, m.z);
}

// Проверка "меньше"
TEST(Monom, can_compare_monom_with_less_operator) 
{
    Monom m1(3.5, 2, 1, 0);
    Monom m2(5.0, 1, 2, 3);
    EXPECT_TRUE(m2 < m1);
}

// Проверка "больше"
TEST(Monom, can_compare_monom_with_greater_operator)
{
    Monom m1(3.5, 2, 1, 0);
    Monom m2(5.0, 1, 2, 3);
    EXPECT_TRUE(m1 > m2);
}

// Проверка "равны" 
TEST(Monom, can_compare_monom_with_equality_operator)
{
    Monom m1(3.5, 2, 1, 0);
    Monom m2(3.5, 2, 1, 0);
    EXPECT_TRUE(m1 == m2);
}



// Проверка создания полинома по умолчанию
TEST(Polynomial, can_create_default_Polynomial)
{
    ASSERT_NO_THROW(Polynomial p);
}

// Провека на пустоту
TEST(Polynomial, can_add_monom_to_Polynomial) 
{
    Polynomial p;
    Monom m(1, 1, 1, 1);
    ASSERT_NO_THROW(p.AddMonom(m));
    EXPECT_FALSE(p.isEmpty());
}

// Проверка упорядоченности мономов в полиноме
TEST(Polynomial, can_add_monoms_and_they_are_ordered) 
{
    Polynomial p;
    p.AddMonom(Monom(1, 2, 1, 0));
    p.AddMonom(Monom(2, 1, 2, 0));
    p.AddMonom(Monom(3, 1, 1, 0));


    p.reset();                          
    EXPECT_EQ(2, p.getCurrent().x);     
    p.goNext();
    EXPECT_EQ(1, p.getCurrent().x);
    EXPECT_EQ(2, p.getCurrent().y);
    p.goNext();
    EXPECT_EQ(1, p.getCurrent().x);
    EXPECT_EQ(1, p.getCurrent().y);
}

// Проверка на корректность склеивания мономов с одинаковыми степенями
TEST(Polynomial, can_add_same_monom_and_coefficients_are_summed)
{
    Polynomial p;
    p.AddMonom(Monom(1, 1, 1, 0));
    p.AddMonom(Monom(2, 1, 1, 0));

    p.reset();
    EXPECT_DOUBLE_EQ(3, p.getCurrent().coeff);
}

// Проверка на самоуничтожение
TEST(Polynomial, can_add_same_monom_and_zero_coefficient_is_deleted)
{
    Polynomial p;
    p.AddMonom(Monom(1, 1, 1, 0));
    p.AddMonom(Monom(-1, 1, 1, 0));

    EXPECT_TRUE(p.isEmpty());
}

// Проверка на корректность отображения
TEST(Polynomial, can_add_monoms_and_Polynomial_is_correctly_displayed)
{
    Polynomial p;
    p.AddMonom(Monom(1, 1, 1, 0));
    p.AddMonom(Monom(2, 2, 0, 0));

    EXPECT_EQ("2x^2y^0z^0 + 1x^1y^1z^0", toString(p));
}

// Проверка отображения пустого полинома
TEST(Polynomial, can_add_monoms_and_Polynomial_is_correctly_displayed_for_zero_Polynomial)
{
    Polynomial p;
    EXPECT_EQ("0", toString(p));
}

// Проверка сложения полиномов
TEST(Polynomial, can_add_Polynomials)
{
    Polynomial p1, p2;
    p1.AddMonom(Monom(1, 1, 1, 0));
    p2.AddMonom(Monom(2, 1, 1, 0));

    Polynomial sum = p1 + p2;
    EXPECT_EQ("3x^1y^1z^0", toString(sum));
}

// Проверка сложения полиномов через "+="
TEST(Polynomial, can_add_assign_Polynomials) 
{
    Polynomial p1, p2;
    p1.AddMonom(Monom(1, 1, 1, 0));
    p2.AddMonom(Monom(2, 1, 1, 0));

    p1 += p2;
    EXPECT_EQ("3x^1y^1z^0", toString(p1));
}

// Проверка вычитания
TEST(Polynomial, can_subtract_Polynomials)
{
    Polynomial p1, p2;
    p1.AddMonom(Monom(3, 1, 1, 0));
    p2.AddMonom(Monom(2, 1, 1, 0));

    Polynomial diff = p1 - p2;
    EXPECT_EQ("1x^1y^1z^0", toString(diff));
}

// Проверка умножения на константу
TEST(Polynomial, can_multiply_Polynomial_by_constant) 
{
    Polynomial p;
    p.AddMonom(Monom(2, 1, 1, 0));

    Polynomial scaled = p * 3.0;
    EXPECT_EQ("6x^1y^1z^0", toString(scaled));
}

// Проверка умножения полинома на моном
TEST(Polynomial, can_multiply_Polynomial_by_monom)
 {
    Polynomial p;
    p.AddMonom(Monom(2, 1, 1, 0));
    Monom m(3, 1, 0, 0);
    Polynomial product = p * m;
    EXPECT_EQ("6x^2y^1z^0", toString(product));
}


// Проверка добавления пустого монома
TEST(Polynomial, can_add_empty_Polynomial) 
{
    Polynomial P;
    Polynomial Q; // пустой
    P += Q;

    EXPECT_EQ("0", toString(P)); 
}

// Проверка добавления нового отличающегося монома
TEST(Polynomial, can_add_Polynomial_without_common_monomials)
{
    Polynomial P, Q;
    P.AddMonom(Monom(2.0, 1, 0, 0)); // 2x
    P.AddMonom(Monom(3.0, 0, 1, 0)); // 3y

    Q.AddMonom(Monom(1.0, 0, 0, 2)); // z²
    Q.AddMonom(Monom(5.0, 2, 0, 0)); // 5x²

    P += Q;
    EXPECT_EQ("5x^2y^0z^0 + 2x^1y^0z^0 + 3x^0y^1z^0 + 1x^0y^0z^2", toString(P));
}

// Проверка добавления нового монома с одинаковыми коэффами
TEST(Polynomial, can_add_Polynomial_with_common_monomials)
{
    Polynomial P, Q;
    P.AddMonom(Monom(2.0, 1, 0, 0)); 
    P.AddMonom(Monom(3.0, 0, 1, 0));

    Q.AddMonom(Monom(-2.0, 1, 0, 0));
    Q.AddMonom(Monom(4.0, 0, 1, 0)); 

    P += Q;

    EXPECT_EQ("7x^0y^1z^0", toString(P)); // y аннулируется, остается 7x
}

// Проверка на правильный порядок, при добавлении в неправильном порядке
TEST(Polynomial, can_add_monom_to_beginning)
{
    Polynomial p;
    p.AddMonom(Monom(1.0, 2, 1, 0));
    p.AddMonom(Monom(3.0, 3, 2, 1)); 
    p.AddMonom(Monom(5.0, 5, 6, 7));
   
    EXPECT_EQ("5x^5y^6z^7 + 3x^3y^2z^1 + 1x^2y^1z^0", toString(p));
}   

// Проверка добавления в конец полинома
TEST(Polynomial, can_add_monom_to_end)
{
    Polynomial p;
    p.AddMonom(Monom(3.0, 3, 2, 1));
    p.AddMonom(Monom(1.0, 1, 5, 0)); 
    p.AddMonom(Monom(7.0, 0, 1, 5));

    EXPECT_EQ("3x^3y^2z^1 + 1x^1y^5z^0 + 7x^0y^1z^5", toString(p));
}

// Проверка добавление я середину полинома
TEST(Polynomial, can_add_monom_to_middle)
{
    Polynomial p;
    p.AddMonom(Monom(3.0, 3, 2, 1)); 
    p.AddMonom(Monom(1.0, 1, 0, 0)); 
    p.AddMonom(Monom(2.0, 2, 1, 0)); 

    EXPECT_EQ("3x^3y^2z^1 + 2x^2y^1z^0 + 1x^1y^0z^0", toString(p));
}

// Проверка присваивания
TEST(Polynomial, assignment_operator_works_correctly)
{
    Polynomial p1, p2;
    p1.AddMonom(Monom(1.0, 1, 0, 0));
    p1.AddMonom(Monom(2.0, 2, 0, 0));
    p1.AddMonom(Monom(3.0, 3, 0, 0));

    p2 = p1;

    EXPECT_EQ(toString(p1), toString(p2));
}

// Проверка сравнения
TEST(Polynomial, equality_operator_returns_true_for_equal_Polynomials) {
    Polynomial p1, p2, p3;
    p1.AddMonom(Monom(1.0, 1, 0, 0));
    p1.AddMonom(Monom(2.0, 2, 0, 0));
    p1.AddMonom(Monom(3.0, 3, 0, 0));

    p2.AddMonom(Monom(1.0, 1, 0, 0));
    p2.AddMonom(Monom(2.0, 2, 0, 0));
    p2.AddMonom(Monom(3.0, 3, 0, 0));

    p3.AddMonom(Monom(3.0, 3, 0, 0));
    p3.AddMonom(Monom(2.0, 2, 0, 0));

    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

// Проверка отображения с отрицательным мономом по середине
TEST(Polynomial, display_negative_monom_in_middle) 
{
    Polynomial p;
    p.AddMonom(Monom(3, 3, 0, 0));
    p.AddMonom(Monom(-2, 2, 0, 0));
    p.AddMonom(Monom(1, 1, 1, 0));

    EXPECT_EQ("3x^3y^0z^0 - 2x^2y^0z^0 + 1x^1y^1z^0", toString(p));
}

// Проверка отображения с отрицательным мономом по середине
TEST(Polynomial, display_negative_monom_at_beginning)
{
    Polynomial p;
    p.AddMonom(Monom(-2, 2, 0, 0));
    p.AddMonom(Monom(1, 1, 1, 0));

    EXPECT_EQ("-2x^2y^0z^0 + 1x^1y^1z^0", toString(p));
}

// Проверка вычитания через "-="
TEST(Polynomial, can_subtract_assign_Polynomial_without_common_monomials)
{
    Polynomial P, Q;
    P.AddMonom(Monom(2.0, 1, 0, 0)); 
    P.AddMonom(Monom(3.0, 0, 1, 0)); 

    Q.AddMonom(Monom(1.0, 0, 0, 2)); 
    Q.AddMonom(Monom(5.0, 2, 0, 0)); 

    P -= Q;

    EXPECT_EQ("-5x^2y^0z^0 + 2x^1y^0z^0 + 3x^0y^1z^0 - 1x^0y^0z^2", toString(P));
}

// Проверка вычитания с общими мономами через "-="
TEST(Polynomial, can_subtract_assign_Polynomial_with_common_monomials)
{
    Polynomial P, Q;
    P.AddMonom(Monom(2.0, 1, 0, 0)); 
    P.AddMonom(Monom(3.0, 0, 1, 0)); 

    Q.AddMonom(Monom(2.0, 1, 0, 0)); 
    Q.AddMonom(Monom(4.0, 0, 1, 0)); 

    P -= Q;
    EXPECT_EQ("-1x^0y^1z^0", toString(P)); 
}

// Проверка на вычитание пустого полинома
TEST(Polynomial, can_subtract_assign_empty_Polynomial)
{
    Polynomial P, Q;
    P.AddMonom(Monom(1.0, 1, 0, 0));

    P -= Q;
    EXPECT_EQ("1x^1y^0z^0", toString(P));
}

// Проверка вычитания из пустого полинома
TEST(Polynomial, can_subtract_assign_Polynomial_from_empty)
{
    Polynomial P, Q;
    Q.AddMonom(Monom(1.0, 1, 0, 0)); // x

    P -= Q;
    EXPECT_EQ("-1x^1y^0z^0", toString(P)); // 0 - x = -x
}

// Проверка умножения полинома на ноль
TEST(Polynomial, multiply_Polynomial_by_zero) 
{
    Polynomial p;
    p.AddMonom(Monom(1.0, 1, 0, 0));
    p.AddMonom(Monom(2.0, 2, 0, 0));

    Polynomial result = p * 0.0;

    EXPECT_EQ("0", toString(result));
}

// Проверка умножения полинома на моном с нулевым коэффом
TEST(Polynomial, multiply_Polynomial_by_monom_with_zero_coeff)
{
    Polynomial p;
    p.AddMonom(Monom(1.0, 1, 0, 0));
    Monom m(0.0, 1, 0, 0);

    Polynomial result = p * m;

    EXPECT_EQ("0", toString(result));
}

// Проверка сложения полиномов с разными степенями мономов
TEST(Polynomial, add_Polynomials_with_different_degrees) 
{
    Polynomial p1, p2;
    p1.AddMonom(Monom(1.0, 1, 0, 0));
    p2.AddMonom(Monom(2.0, 2, 0, 0));

    Polynomial sum = p1 + p2;

    EXPECT_EQ("2x^2y^0z^0 + 1x^1y^0z^0", toString(sum));
}

// Проверка вычитания полиномов с мономами с разными степенями
TEST(Polynomial, subtract_Polynomials_with_different_degrees) 
{
    Polynomial p1, p2;
    p1.AddMonom(Monom(2.0, 2, 0, 0));
    p2.AddMonom(Monom(1.0, 1, 0, 0));

    Polynomial diff = p1 - p2;

    EXPECT_EQ("2x^2y^0z^0 - 1x^1y^0z^0", toString(diff));
}

// Проверка умножения полинома на пустой
TEST(Polynomial, multiply_Polynomial_by_empty_Polynomial) 
{
    Polynomial p1, p2;

    p1.AddMonom(Monom(2, 1, 0, 0));
    p1.AddMonom(Monom(3, 0, 1, 0));

    Polynomial result = p1 * p2;

    EXPECT_EQ("0", toString(result));
}

// Проверка умножения полинома на полином
TEST(Polynomial, multiply_Polynomial_by_Polynomial)
{
    Polynomial p1, p2;

    p1.AddMonom(Monom(2, 1, 0, 0));
    p1.AddMonom(Monom(3, 0, 1, 0));


    p2.AddMonom(Monom(1, 0, 0, 1));
    p2.AddMonom(Monom(4, 2, 0, 0));

    Polynomial result = p1 * p2;

    EXPECT_EQ("8x^3y^0z^0 + 12x^2y^1z^0 + 2x^1y^0z^1 + 3x^0y^1z^1", toString(result));
}

// Проверка умножения полинома на полином с отрицательными мономами 
TEST(Polynomial, multiply_Polynomial_by_Polynomial_with_negative_coefficients) 
{
    Polynomial p1, p2;

    p1.AddMonom(Monom(-2, 1, 0, 0));
    p1.AddMonom(Monom(3, 0, 1, 0));

    p2.AddMonom(Monom(1, 0, 0, 1));
    p2.AddMonom(Monom(-4, 2, 0, 0));

    Polynomial result = p1 * p2;

    EXPECT_EQ("8x^3y^0z^0 - 12x^2y^1z^0 - 2x^1y^0z^1 + 3x^0y^1z^1", toString(result));
}

// Проверка умножения полинома на полином с мономами с одинаковыми степенями
TEST(Polynomial, multiply_Polynomial_by_Polynomial_with_same_degrees)
{
    Polynomial p1, p2;

    // p1 = x + x = 2x
    p1.AddMonom(Monom(1, 1, 0, 0));
    p1.AddMonom(Monom(1, 1, 0, 0));

    // p2 = x + x = 2x
    p2.AddMonom(Monom(1, 1, 0, 0));
    p2.AddMonom(Monom(1, 1, 0, 0));

    Polynomial result = p1 * p2;

    EXPECT_EQ("4x^2y^0z^0", toString(result));
}