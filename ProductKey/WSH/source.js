var ProductKey = ProductKey || {
  DecodeProductKey : function(digitalProductId) {
    var map = ('BCDFGHJKMPQRTVWXY2346789').split(''),
        key = [], raw, i, j;
        
    with (new ActiveXObject('WScript.Shell'))
      raw = RegRead(digitalProductId).toArray().slice(52, 67);
      
    for (i = 24; i >= 0; i--) {
      var k = 0;
      for (j = 14; j >= 0; j--) {
        k = (k * 256) ^ raw[j];
        raw[j] = Math.floor(k / 24);
        k %= 24;
      }
      key = map[k] + key;
      
      if ((i % 5) == 0 && i != 0) key = '-' + key;
    }
    return key;
  },
  
  GetProductKey : function() {
    var key = 'HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\DigitalProductId';
    return this.DecodeProductKey(key);
  }
};

WScript.echo(ProductKey.GetProductKey());
