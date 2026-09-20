package com.example.calculator;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import io.swagger.v3.oas.annotations.Operation;
import io.swagger.v3.oas.annotations.tags.Tag;

@RestController
@RequestMapping("/calculator")
@Tag(name = "Calculator", description = "Simple Calculator REST API")
public class CalculatorController {

    @Operation(summary = "Add two numbers", description = "Returns the sum of two numbers")
    @GetMapping("/add")
    public double add(
            @RequestParam double a,
            @RequestParam double b) {
        return a + b;
    }

    @Operation(summary = "Subtract two numbers", description = "Returns the difference of two numbers")
    @PostMapping("/subtract")
    public double subtract(
            @RequestParam double a,
            @RequestParam double b) {
        return a - b;
    }

    @Operation(summary = "Multiply two numbers", description = "Returns the product of two numbers")
    @PutMapping("/multiply")
    public double multiply(
            @RequestParam double a,
            @RequestParam double b) {
        return a * b;
    }

    @Operation(summary = "Divide two numbers", description = "Returns the quotient of two numbers")
    @PutMapping("/divide")
    public double divide(
            @RequestParam double a,
            @RequestParam double b) {
        return a / b;
    }

}