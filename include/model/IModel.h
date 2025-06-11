#include<iostream>

template <typename T = double>
class IModel {
    public:
        virtual void fit(const std::vector<std::vector<T>>& X,
                         const std::vector<T>& y) = 0;
        virtual T predict(const std::vector<T>& x) const = 0;
        virtual std::vector<T> predictBatch(const std::vector<std::vector<T>>& X) const;

        virtual ~IModel() = default;
};