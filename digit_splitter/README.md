#Digit splitter
based on the original idea by Rahulkar
code extracted from instructable: "7 Segment Digital Thermometer using ATtiny 85" @http://www.instructables.com/id/7-Segment-Digital-Thermometer-using-ATtiny-85/
simple example of code used to "separate" or "split" the digits in a float number, eg 123.32 -> (1-2-3-3-2).
it relies on the modulo opeartor (%) and the ability of separating the decimals from the original numbe
and then transform them to an integer variable so modulo can work.
My interest is to apply it when dealing with float numbers and
want to print them over a 7-segment display.
