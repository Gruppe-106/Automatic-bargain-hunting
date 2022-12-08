package com.g106.util;

import java.util.Locale;

public class ItemData {

    public static class PricePrUnit {
        public Float price;
        public String unit;

        public PricePrUnit() {
            this.price = 0f;
            this.unit = "";
        }

        public String toString() {
            return "Price per unit: " + this.price + " / " + this.unit;
        }
    }

    public static class Item {
        public String name;
        public String brand;
        public Float price;
        public PricePrUnit price_pr_unit;
        public Float unit_size;
        public String unit_type;

        public Item() {
            this.name = "";
            this.brand = "";
            this.price = 0f;
            this.price_pr_unit = new PricePrUnit();
            this.unit_size = 0f;
            this.unit_type = "";
        }

        public void setPrice_pr_unit(float price, String unit) {
            this.price_pr_unit.unit = asAscii(unit);
            this.price_pr_unit.price = price;
        }

        public void setUnit_type(String unit_type) {
            this.unit_type = asAscii(unit_type);
        }

        public void setBrand(String brand) {
            this.brand = asAscii(brand);
        }

        public void setName(String name) {
            this.name = asAscii(name);
        }

        private String asAscii(String string) {
            return string.toLowerCase(Locale.ROOT)
                    .replace("æ", "ae")
                    .replace("ø", "oe")
                    .replace("å", "aa")
                    .replace("ä", "a")
                    .replace("ë", "e")
                    .replace("ö", "o")
                    .replace("ü", "u")
                    .replace("ï", "i")
                    .replace("ÿ", "y")
                    .replace("é", "e")
                    .replace("á", "a")
                    .replace("í", "i")
                    .replace("ó", "o")
                    .replace("ú", "u")
                    .replace("&", "og");
        }

        public String toString() {
            return  "Name: " + this.name + "\n" +
                    "Brand: " + this.brand + "\n" +
                    "Price: " + this.price + "\n" +
                     price_pr_unit.toString() + "\n" +
                    "Size: " + this.unit_size + " " + this.unit_type;
        }
    }

}
