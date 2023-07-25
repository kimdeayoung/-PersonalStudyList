package academy.pocu.comp2500.lab2;

public class ComplexNumber {
    public double real;
    public double imaginary;

    public ComplexNumber() {
        this(0.0, 0.0);
    }

    public ComplexNumber(double real) {
        this(real, 0.0);
    }

    public ComplexNumber(double real, double imaginary) {
        this.real = real;
        this.imaginary = imaginary;
    }

    public boolean isReal() {
        if (imaginary == 0.0) {
            return true;
        }
        return false;
    }

    public boolean isImaginary() {
        if (real == 0.0) {
            return true;
        }
        return false;
    }

    public ComplexNumber getConjugate() {
        ComplexNumber result = new ComplexNumber(this.real, -this.imaginary);
        return result;
    }

    public ComplexNumber add(ComplexNumber num) {
        ComplexNumber result = new ComplexNumber((this.real + num.real), (this.imaginary + num.imaginary));
        return result;
    }

    public ComplexNumber subtract(ComplexNumber num) {
        ComplexNumber result = new ComplexNumber((this.real - num.real), (this.imaginary - num.imaginary));
        return result;
    }

    public ComplexNumber multiply(ComplexNumber num) {
        double real = this.real * num.real - this.imaginary * num.imaginary;
        double imaginary = this.real * num.imaginary + this.imaginary * num.real;

        ComplexNumber result = new ComplexNumber(real, imaginary);
        return result;
    }

    public ComplexNumber divide(ComplexNumber num) {
        double real = this.real * num.real + this.imaginary * num.imaginary;
        double imaginary = -(this.real * num.imaginary) + this.imaginary * num.real;

        double rhf = (num.real * num.real + num.imaginary * num.imaginary);//나눗셈 우항

        ComplexNumber result = new ComplexNumber(real / rhf, imaginary / rhf);
        return result;
    }
}
