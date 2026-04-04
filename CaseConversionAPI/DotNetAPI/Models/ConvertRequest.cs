namespace StringConversionAPI.Models
{
    public class ConvertRequest
    {
        public string Text { get; set; } = string.Empty;
        public int Choice { get; set; }
    }
}