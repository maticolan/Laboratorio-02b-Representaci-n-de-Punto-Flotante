#include <iostream>
#include <bitset>

using namespace std;

// Función para multiplicar dos números flotantes
float multiplicar(float x, float y) {
    // 1. Recibir los valores en variables float de 32 bits
    float a = x;
    float b = y;

    // 2. Separar los patrones de bits
    bitset sign_a = a >> 31;
    bitset exponent_a = a >> 23 & 0xFF;
    bitset significand_a = a & 0x7FFFFFFF;

    bitset sign_b = b >> 31;
    bitset exponent_b = b >> 23 & 0xFF;
    bitset significand_b = b & 0x7FFFFFFF;

    // 3. Multiplicar los significandos
    bitset significand_product = significand_a * significand_b;

    // 4. Normalizar el producto
    int leading_zeros = 0;
    for (int i = 0; i < 46; i++) {
        if (significand_product[i]) {
            leading_zeros = i;
            break;
        }
    }

    significand_product = significand_product >> leading_zeros;

    // 5. Reajustar el exponente
    int exponent_product = exponent_a + exponent_b - 127 + leading_zeros - 1;

    // 6. Comprobar overflow y underflow
    if (exponent_product > 127) {
        // Overflow
        cout << "Error: Overflow de exponente" << endl;
        return 0;
    }
    else if (exponent_product < -127) {
        // Underflow
        cout << "Error: Underflow de exponente" << endl;
        return 0;
    }

    // 7. Ensamblar el resultado
    bitset result = sign_a | (exponent_product << 23) | significand_product;

    // 8. Devolver el resultado
    return float(result);
}

int main() {
    // Declarar los operandos
    float x = 1.23456789;
    float y = 2.34567890;

    // Multiplicar los operandos
    float resultado = multiplicar(x, y);

    // Imprimir el resultado
    cout << "El resultado es " << resultado << endl;

    return 0;
}