//
// Created by elnchou on 10-06-26.
//

#include "../../macros.hp"
#include <memory>
#include <vector>
#include <random>

/// parametro lambda para la distribución
constexpr double lambda = 0.008;
/// Generador global, que se usa para elegir semillas al azar.
inline std::random_device rd;

class RandomValues {
private:
    /// Cantidad de valores generados por esta estructura en la inicialización.
    std::size_t N;
    /// Vector que almacena los valores generados en la inicialización.
    std::vector<uint> dataset;
    /// Vector que almacena las probabilidades como discrete distribution
    std::discrete_distribution<uint> probs;
    /// Generador de números aleatorios
    std::mt19937_64 rng;

    /**
     * Genera un índice al azar dentro del rango de Dataset, el cual posteriormente se puede
     * extraer.
     * @param uniform Indica si se utilizará una distribución uniforme sencilla o la sesgada
     * @return Un índice entre 0 y N-1 que permita obtener un elemento de dataset.
     */
    uint generateIdx(bool uniform = false);
    /** Genera un valor al azar del rango de unsigned int */
    uint generateRandUint();
    /// Actualiza la probabilidad sesgada con tal de utilizarla lueguito
    void updateProbs();
public:
    /**
     * Crea un dataset de valores al azar (en un unsigned int) con un tamaño dado, el cual
     * será utilizado para entregar los valores aleatorios.
     * @param howMany Tamaño del dataset a crear. Debe ser una potencia de 2.
     * @param seed Semilla que utilizará el mersenne twister
     */
    RandomValues(std::size_t howMany, uint seed = rd());

    /**
     * Crea el generador aleatorio a partir de un dataset ya calculado.
     * Útil si se desea generar un dataset sin consumir la aleatoriedad interna de la semilla.
     * @param data Vector que será copiado para contener el dataset.
     * @param seed Semilla que utilizará el mersenne twister.
     */
    RandomValues(const std::vector<uint> &data, uint seed = rd());

    /**
     * Obtiene valores aleatorios de los almacenados dentro de esta estructura.
     * @param quantity Cantidad de valores que se quieren obtener. (Se pueden repetir)
     * @param uniformDist Indica si se eligen los valores de forma uniforme, o si se usa la distribución sesgada interna.
     * @return Vector de valores aleatorios entre los almacenados por esta estructura. Lanza error si no tiene ninguno.
     */
    std::vector<uint> getVal(std::size_t quantity, bool uniformDist = true);

    /**
     * Obtiene un único valor aleatorio de los almacenados dentro de esta estructura.
     * @param uniformDist Indica si se eligen los valores de forma uniforme, o si se usa la distribución sesgada interna.
     * @return Valor aleatorio entre los almacenados por esta estructura. Lanza error si no tiene ninguno.
     */
    uint generate(bool uniformDist = true);

    /**
     * Retorna un índice específico de los datos.
     * @param i
     * @return El índice de la cosa
     */
    uint const &operator[](uint i) const;
};