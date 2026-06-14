//
// Created by elnchou on 10-06-26.
//

#include "../../macros.hp"
#include <memory>
#include <vector>
#include <random>

constexpr double lambda = 0.008; // parametro lambda para la distribución

class RandomValues {
private:
    /// Cantidad de valores generados por esta estructura en la inicialización.
    std::size_t N;
    /// Vector que almacena los valores generados en la inicialización.
    std::vector<uint> dataset;
    /// Vector que almacena las probabilidades como discrete distribution
    std::discrete_distribution<uint> probs;
    uint generateIdx();
    static uint generateRandUint();
    //static ullong calcProb(uint i);
public:
    RandomValues(std::size_t howMany);
    /**
     * Obtiene valores aleatorios de los almacenados dentro de esta estructura.
     * @param quantity Cantidad de valores que se quieren obtener. (Se pueden repetir)
     * @return Valor aleatorio entre los almacenados por esta estructura. Lanza error si no tiene ninguno.
     */
    std::vector<uint> getVal(std::size_t quantity);

    /**
     * Retorna un índice específico de los datos.
     * @param i
     * @return El índice de la cosa
     */
    uint const &operator[](uint i) const;
};