// Copyright (c) 2018 Grumpy Cat Software S.L.
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa.h>

af::array tsa::features::absoluteSumOfChanges(af::array tss) {
    long n = tss.dims(0);
    return af::sum(af::abs(tss(af::seq(std::min(1L, n - 1), n - 1), span) - tss(af::seq(0, std::max(0L, n - 2)), span)), 0);
}

af::array tsa::features::absEnergy(af::array base){
    array p2 = af::pow(base, 2);
    af::array sp2 = af::sum(p2, 0);
    return sp2;
}

af::array aggregating(af::array input, af::array (*aggregationFunction)(const af::array&, const int)) {
    return aggregationFunction(input, -1);
}

af::array aggregating(af::array input, af::array (*aggregationFunction)(const af::array&, const dim_t)) {
    return aggregationFunction(input, -1);
}

af::array aggregatingOnChunks(af::array input, long chunkSize, af::array (*aggregationFunction)(const af::array&, const int)) {
    af::array inputChunks = af::join(0, input, af::constant(0, (input.dims(0)%chunkSize == 0)? 0: chunkSize - input.dims(0)%chunkSize, input.dims(1), input.type()));
    inputChunks = af::moddims(inputChunks, chunkSize, inputChunks.dims(0)/chunkSize, inputChunks.dims(1));
    return af::reorder(af::transpose(aggregationFunction(inputChunks, 0)), 0, 2, 1, 3);
}

af::array aggregatingOnChunks(af::array input, long chunkSize, af::array (*aggregationFunction)(const af::array&, const dim_t)) {
    af::array inputChunks = af::join(0, input, af::constant(0, (input.dims(0)%chunkSize == 0)? 0: chunkSize - input.dims(0)%chunkSize, input.dims(1), input.type()));
    inputChunks = af::moddims(inputChunks, chunkSize, inputChunks.dims(0)/chunkSize, inputChunks.dims(1));
    return af::reorder(af::transpose(aggregationFunction(inputChunks, 0)), 0, 2, 1, 3);
}

void tsa::features::aggregatedLinearTrend(af::array t, long chunkSize, af::array (*aggregationFunction)(const af::array&, const int),
                                            af::array &slope, af::array &intercept, af::array &rvalue, af::array &pvalue, af::array &stderrest) {
    af::array aggregateResult = aggregatingOnChunks(t, chunkSize, aggregationFunction);
    tsa::regression::linear(af::tile(af::range(aggregateResult.dims(0)).as(t.type()), 1, t.dims(1)), aggregateResult, slope, intercept, rvalue, pvalue, stderrest);
}

void tsa::features::aggregatedLinearTrend(af::array t, long chunkSize, af::array (*aggregationFunction)(const af::array&, const dim_t),
                                            af::array &slope, af::array &intercept, af::array &rvalue, af::array &pvalue, af::array &stderrest) {
    af::array aggregateResult = aggregatingOnChunks(t, chunkSize, aggregationFunction);
    tsa::regression::linear(af::tile(af::range(aggregateResult.dims(0)).as(t.type()), 1, t.dims(1)), aggregateResult, slope, intercept, rvalue, pvalue, stderrest);
}

af::array tsa::features::autocorrelation(af::array tss, long lag) {
    long n = tss.dims(0);

    af::array y1 = tss(af::seq(n - lag), span);
    af::array y2 = tss(af::seq(lag, n - 1), span);
    
    af::array xMean = af::mean(tss, 0);

    af::array sumProduct = af::sum((y1 - af::tile(xMean, n - lag)) * (y2 - af::tile(xMean, n - lag)), 0);
    af::array den = (n - lag) * af::var(tss, true, 0);
    return sumProduct / den;
}

af::array tsa::features::c3(af::array tss, long lag) {
    af::array aux = af::shift(tss, 2 * -lag) * af::shift(tss, -lag) * tss;
    return af::mean(aux(af::seq(tss.dims(0) - 2 * lag), span), 0);
}

af::array tsa::features::cidCe(af::array tss, bool zNormalize) {
    long n = tss.dims(0);
    if (zNormalize) {
        tsa::normalization::znormInPlace(tss);
    }

    af::array diff = tss(af::seq(std::min(1L, n - 1), n - 1), span) - tss(af::seq(0, std::max(0L, n - 2)), span);
    return af::sqrt(af::sum(diff * diff));
}

af::array tsa::features::countBelowMean(af::array tss) {
    af::array mean = af::mean(tss, 0);
    af::array belowMean = (tss < af::tile(mean, tss.dims(0))).as(af::dtype::u32);
    return af::sum(belowMean, 0);
}

af::array tsa::features::energyRatioByChunks(af::array tss, long numSegments, long segmentFocus) {
    af::array fullSeriesEnergy = tsa::features::absEnergy(tss);
    long n = tss.dims(0);
    long segmentLength = n/numSegments;
    long start = segmentFocus * segmentLength;
    long end = std::min((segmentFocus + 1) * segmentLength, n);
    return tsa::features::absEnergy(tss(af::seq(start, end - 1), span)) / fullSeriesEnergy;
}

void tsa::features::fftCoefficient(af::array tss, long coefficient, af::array &real, af::array &imag, af::array &_abs,
                    af::array &angle) {
    af::array fft = af::fft(tss);
    af::array fftCoefficient = fft(coefficient, span);
    real = af::real(fftCoefficient);
    imag = af::imag(fftCoefficient);
    _abs = af::abs(real);
    angle = af::arg(fftCoefficient);
}

af::array tsa::features::firstLocationOfMinimum(af::array tss) {
    af::array flipped = af::flip(tss, 0);

    af::array minimum;
    af::array index;

    af::min(minimum, index, flipped, 0);

    index = af::abs(index - tss.dims(0) + 1);

    return index.as(tss.type()) / tss.dims(0);
}

af::array tsa::features::hasDuplicates(af::array tss) {
    af::array result = af::array(tss.dims(1), af::dtype::b8);

    for(long i = 0; i < tss.dims(1); i++) {
        af::array uniq = af::setUnique(tss(span, i));
        result(i) = tss.dims(0) != uniq.dims(0);
    }
    
    return af::transpose(result);
}

af::array tsa::features::hasDuplicateMin(af::array tss) {
    af::array minimum = af::min(tss, 0);

    return af::sum(tss == af::tile(minimum, tss.dims(0)), 0) > 1;
}

af::array tsa::features::kurtosis(af::array tss) {
    return tsa::statistics::kurtosis(tss);
}

#ifdef __cplusplus
extern "C" {
#endif
    void cidCe(double* tss, long* tss_length, long* tss_number_of_tss, bool* zNormalize, double* result){
        af::array primitive_result;
        primitive_result = tsa::features::cidCe(af::array(*tss_length, *tss_number_of_tss, tss), *zNormalize);
        primitive_result.host(result);
    }

    void abs_energy(double* time_series, long* time_series_length, long* number_of_time_series, double* primitive_result) {
        af::array result;
        result = tsa::features::absEnergy(af::array(*time_series_length, *number_of_time_series, time_series));
        result.host(primitive_result);
    }

    void absolute_sum_of_changes(double* time_series, long* time_series_length, long* number_of_time_series, double* primitive_result) {
        af::array result;
        result = tsa::features::absoluteSumOfChanges(af::array(*time_series_length, *number_of_time_series, time_series));
        result.host(primitive_result);
    }

    void c3(double* tss, long* tss_length, long* tss_number_of_tss, long* lag, double* result){
        af::array primitive_result;
        primitive_result = tsa::features::c3(af::array(*tss_length, *tss_number_of_tss, tss),*lag);
        primitive_result.host(result);
    }
    
    JNIEXPORT void JNICALL Java_tsa_TSA_c3(JNIEnv *env, jobject thisObj, jdoubleArray tss, jlong tssLength, jlong tssNumberOfTss,
                                             jlong lag, jdoubleArray result){
        af::array primitive_result;
        long tssFull_length = tssLength * tssNumberOfTss;
        double input_tss[tssFull_length];
        env->GetDoubleArrayRegion(tss, 0, tssFull_length, &input_tss[0]);

        primitive_result = tsa::features::c3(af::array(tssLength, tssNumberOfTss, input_tss),lag);

        double output_result[tssNumberOfTss];
        primitive_result.host(output_result);
        env->SetDoubleArrayRegion(result, 0, tssNumberOfTss, &output_result[0]);
        return;
    }   

    JNIEXPORT void JNICALL Java_tsa_TSA_cidCe(JNIEnv *env, jobject thisObj, jdoubleArray tss, jlong tssLength, jlong tssNumberOfTss, 
                                                jboolean zNormalize, jdoubleArray result){
        af::array primitive_result;
        long tssFull_length = tssLength * tssNumberOfTss;
        double input_tss[tssFull_length];
        env->GetDoubleArrayRegion(tss, 0, tssFull_length, &input_tss[0]);

        primitive_result = tsa::features::cidCe(af::array(tssLength, tssNumberOfTss, input_tss),zNormalize);

        double output_result[tssNumberOfTss];
        primitive_result.host(output_result);
        env->SetDoubleArrayRegion(result, 0, tssNumberOfTss, &output_result[0]);
        return;
    }
    
    
    JNIEXPORT void JNICALL Java_tsa_TSA_absEnergy(JNIEnv *env, jobject thisObj, jdoubleArray timeSeries, jlong timeSeriesLength, 
                                                    jlong numberOfTimeSeries, jdoubleArray jResult) {
        af::array result;

        long concatenatedTimeSeriesLength = timeSeriesLength * numberOfTimeSeries;

        double inputTs[concatenatedTimeSeriesLength];

        env->GetDoubleArrayRegion(timeSeries, 0, concatenatedTimeSeriesLength, &inputTs[0]);

        result = tsa::features::absEnergy(af::array(timeSeriesLength, numberOfTimeSeries, inputTs));

        double inputCResult[numberOfTimeSeries];

        result.host(inputCResult);

        env->SetDoubleArrayRegion(jResult, 0, numberOfTimeSeries, &inputCResult[0]);

        return;
    }

    JNIEXPORT void JNICALL Java_tsa_TSA_absoluteSumOfChanges(JNIEnv *env, jobject thisObj, jdoubleArray timeSeries,
                                                        jlong timeSeriesLength, jlong numberOfTimeSeries, jdoubleArray jResult) {
        af::array result;

        long concatenatedTimeSeriesLength = timeSeriesLength * numberOfTimeSeries;

        double inputTs[concatenatedTimeSeriesLength];

        env->GetDoubleArrayRegion(timeSeries, 0, concatenatedTimeSeriesLength, &inputTs[0]);

        result = tsa::features::absoluteSumOfChanges(af::array(timeSeriesLength, numberOfTimeSeries, inputTs));

        double inputCResult[numberOfTimeSeries];

        result.host(inputCResult);

        env->SetDoubleArrayRegion(jResult, 0, numberOfTimeSeries, &inputCResult[0]);

        return;
    }

#ifdef __cplusplus
}
#endif
