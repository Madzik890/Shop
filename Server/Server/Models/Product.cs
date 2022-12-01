namespace Server.Models;

public class Product
{
    public Product(String name, Double price, Double weight)
    {
        Name = name;
        Price = price;
        Weight = weight;
    }
    
    public String Name { get; set; } = null!;
    public Double Price { get; set; }
    public Double Weight { get; set; }
}