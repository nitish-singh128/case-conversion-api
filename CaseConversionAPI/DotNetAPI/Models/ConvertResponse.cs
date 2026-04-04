namespace StringConversionAPI.Models
{
    public class ConvertResponse
    {
        public string Input { get; set; } = string.Empty;
        public int Choice { get; set; }
        public string Output { get; set; } = string.Empty;
    }
}