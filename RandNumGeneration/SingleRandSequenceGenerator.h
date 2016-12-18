////
//// Created by CUI Shidong on 12/7/2016.
////
//
//#ifndef FINANCE_RANDOMSEQUENCEGENERATOR_H
//#define FINANCE_RANDOMSEQUENCEGENERATOR_H
//
//#include "UniformLEcuyerRNG1.h"
//#include <vector>
//
//using std::vector;
//
////class RNGComponent {
////public:
////    virtual const vector<double> &next() = 0;
////
////    virtual const vector<double> &last() = 0;
////
////    virtual unsigned long getDimension() const = 0;
////
////    virtual void setDimension(unsigned long dimension) = 0;
////
////    virtual ~RNGComponent() { }
////};
//
///* decorator pattern */
//template<typename RNG>
//class SingleRandSequenceGenerator : public GenericRandomVariableGenerator {
//public:
//    SingleRandSequenceGenerator() = default;
//
//    SingleRandSequenceGenerator(vector<double>::size_type dimension);
//
////    void setDimension(unsigned long dimension) override;
//
////    const vector<double> &next() override;
//
////    const vector<double> &last() override { return sequence_; }
//
////    unsigned long getDimension() const override { return dimension_; }
//
//private:
//    RNG rng_;
//    unsigned long dimension_;
//    vector<double> sequence_;
//};
//
//template<typename RNG>
//SingleRandSequenceGenerator<RNG>::SingleRandSequenceGenerator(vector<double>::size_type dimension)
//        : dimension_(
//        dimension), rng_() {
//    sequence_.resize(dimension_);
//}
//
//template<typename RNG>
//const vector<double> &SingleRandSequenceGenerator<RNG>::next() {
//    for (int i = 0; i < dimension_; i++) {
//        sequence_[i] = rng_.next();
//    }
//    return sequence_;
//}
//
//template<typename RNG>
//void SingleRandSequenceGenerator<RNG>::setDimension(unsigned long dimension) {
//    dimension_ = dimension;
//}
//
//#endif //FINANCE_RANDOMSEQUENCEGENERATOR_H
