package com.g106.util;

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

        public String toString() {
            return  "Name: " + this.name + "\n" +
                    "Brand: " + this.brand + "\n" +
                    "Price: " + this.price + "\n" +
                     price_pr_unit.toString() + "\n" +
                    "Size: " + this.unit_size + " " + this.unit_type;
        }
    }

}
