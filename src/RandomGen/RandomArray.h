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
    uint generateIdx(bool uniform = false);
    static uint generateRandUint();
public:
    /**
     * Crea un dataset de valores al azar (en un unsigned int) con un tamaño dado, el cual
     * será utilizado para entregar los valores aleatorios.
     * @param howMany Tamaño del dataset a crear. Debe ser una potencia de 2.
     */
    RandomValues(std::size_t howMany);
    /**
     * Obtiene valores aleatorios de los almacenados dentro de esta estructura.
     * @param quantity Cantidad de valores que se quieren obtener. (Se pueden repetir)
     * @param uniformDist Indica si se eligen los valores de forma uniforme, o si se usa la distribución sesgada interna.
     * @return Valor aleatorio entre los almacenados por esta estructura. Lanza error si no tiene ninguno.
     */
    std::vector<uint> getVal(std::size_t quantity, bool uniformDist = true);

    /**
     * Retorna un índice específico de los datos.
     * @param i
     * @return El índice de la cosa
     */
    uint const &operator[](uint i) const;
};