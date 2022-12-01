using Microsoft.AspNetCore.Mvc;
using Server.Models;

namespace Server.Controllers;

[ApiController]
[Route("[controller]")]
public class ShopController  : ControllerBase
{
    private static readonly List<Product> ProductsList = new List<Product>
    {
        new Product("Pepsi", 7.0, 2.0),
        new Product("Pepsi Zero", 7.0, 2.0),
        new Product("Lays", 10.0, 0.2),
        new Product("Star Chips", 5.0, 0.2),
        new Product("Ibuprofen", 7.0, 0.1)
    }; 

    private readonly ILogger<ShopController> _logger;
    
    public ShopController(ILogger<ShopController> logger)
    {
        _logger = logger;
    }
    
    [HttpGet("/getProducts")]
    public IEnumerable<Product> GetProducts()
    {
        return ProductsList;
    }
}