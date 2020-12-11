//
// Created by Pavel Akhtyamov on 02.05.2020.
//

#include "WeatherTestCase.h"
#include "WeatherMock.h"

TEST(WeatherTest, GetResponseForCity){
    WeatherMock w;
    cpr::Response response_bad;
    cpr::Response response_ok;
    response_ok.status_code = 200;
    response_bad.status_code = 400;
    response_ok.text = "{\"default\":\"some_text\"}";

    EXPECT_CALL(w, Get("ололо")).WillRepeatedly(testing::Return(response_bad));
    EXPECT_THROW(w.GetResponseForCity("ололо"), std::invalid_argument);

    EXPECT_CALL(w, Get("London")).WillRepeatedly(testing::Return(response_ok));
    EXPECT_NO_THROW(w.GetResponseForCity("London"));
}

TEST(WeatherTest, FindDiffBetweenTwoCities){
    WeatherMock w;
    cpr::Response response;

    response.status_code = 200;
    response.text = "{\"list\" : [{\"main\": {\"temp\": -5}}]}";

    EXPECT_CALL(w, Get("London")).WillRepeatedly(testing::Return(response));
    EXPECT_FLOAT_EQ(w.FindDiffBetweenTwoCities("London", "London"), 0);
}

TEST(WeatherTest, GetTemperature){
    WeatherMock w;
    cpr::Response response;
    response.status_code = 200;
    response.text = "{\"list\": [{\"main\": {\"temp\": 289}}]}";

    EXPECT_CALL(w, Get("London")).WillOnce(testing::Return(response));
    EXPECT_EQ(w.GetTemperature("London"), 289);
}

TEST(WeatherTest, GetDifferenceString){
    WeatherMock w;

    cpr::Response response1;
    cpr::Response response2;

    response1.status_code = 200;
    response2.status_code = 200;

    response1.text = "{\"list\" : [{\"main\": {\"temp\": 15}}]}";
    response2.text = "{\"list\" : [{\"main\": {\"temp\": 28}}]}";

    EXPECT_CALL(w, Get("London")).WillRepeatedly(testing::Return(response1));
    EXPECT_CALL(w, Get("Sochi")).WillRepeatedly(testing::Return(response2));

    ASSERT_EQ(w.GetDifferenceString("London", "Sochi"), "Weather in London is colder than in Sochi by 13 degrees");
    ASSERT_EQ(w.GetDifferenceString("Sochi", "London"), "Weather in Sochi is warmer than in London by 13 degrees");
}

TEST(WeatherTest, SetApiKey) {
    WeatherMock weather;
    ASSERT_NO_THROW(weather.SetApiKey("api_key"));
}
