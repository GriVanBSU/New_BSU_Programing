
[TestClass] 
public class FactorialCollectorTests
{ 
    [TestMethod] 
    public void GetFactorialRowTest() 
    { 
        var testList = new List<long>() { 1, 2, 3, 4, 5 }; 
 
        string expectedStr = "1 2 6 24 120"; 
 
        var resultList = FactorialCollector.getFactorialRow(testList);
 
        StringBuilder sbResult = new StringBuilder; 
        foreach( var item in resultList )  
        { 
            sbResult.Append( item.ToString() ); 
            sbResult.Append( " " ); 
        } 
 
        string resultStr = sbResult.ToString(); 
 
        Assert.AreEqual(expectedStr, resultStr); 
    } 
}
