import java.util.Locale;

public class BaseConverter {
    public enum TemperatureScale {
        CELSIUS,
        KELVIN,
        FAHRENHEIT
    }
    private Locale locale;
    public BaseConverter(Locale locale) {

        this.locale = locale;
    }
    public double convert(double temperature, TemperatureScale toScale) {
        switch (toScale) {
            case CELSIUS:
                return temperature;
            case KELVIN:
                return temperature + 273.15;
            case FAHRENHEIT:
                return (temperature * 9 / 5) + 32;
            default:
                throw new IllegalArgumentException("Unsupported temperature scale");
        }
    }
    public static BaseConverter createWithDefaultLocale() {
        Locale defaultLocale = Locale.getDefault();
        return new BaseConverter(defaultLocale);
    }
    public boolean isFahrenheitCountry() {
        String countryCode = locale.getCountry();
        String[] fahrenheitCountries = {"BS", "US", "BZ", "KY", "PW"};
        for (String country : fahrenheitCountries) {
            if (countryCode.equals(country)) {
                return true;
            }
        }
        return false;
    }
}
