<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      xmlns:msxsl="urn:schemas-microsoft-com:xslt"
      xmlns:dedek="http://reportasistent.com/dedek_namespace"
      version="1.0">

  
  <msxsl:script language="JScript" implements-prefix="dedek">

    function round(val)
    {
    if (val == 0 &amp;&amp; (val != parseInt(val))) return val;
    if (val == parseInt(val)) return val;

    var n = new Number(0.5);
    var sep = n.toLocaleString().charAt(1);

    var rep = val.replace(sep, ".");

    n = new Number(rep);

    if (isNaN(n))
    {
    return val;
    }
    else
    {
    return n.toLocaleString();
    }

    }

  </msxsl:script>





  <xsl:template match="attr_link_table">

    <xsl:text disable-output-escaping="yes">
		</xsl:text>
    <output>
      <paragraph>
        <xsl:variable name="rows_count" select="count(link)"/>
        <table id="tab{@id}" cols="2" rows="{$rows_count}">
          <xsl:apply-templates select="link">
            <xsl:with-param name="target_active_element">
              <xsl:value-of select="@target"/>
            </xsl:with-param>
          </xsl:apply-templates>



          <xsl:text disable-output-escaping="yes">
		
		</xsl:text>
        </table>
      </paragraph>
    </output>
  </xsl:template>






  <xsl:template match="link">
    <xsl:param name="target_active_element" />

    <xsl:text disable-output-escaping="yes">
		
				</xsl:text>
    <tr id="tr_attr_{@attr_name}">

      <xsl:variable name="attr_name" select="@attr_name"/>


      <xsl:text disable-output-escaping="yes">
					</xsl:text>

      <td>
        <text id="txt1">
          <xsl:value-of select="@caption"/>
        </text>
      </td>
      <td>
        <text id="txt2">
<!--      <xsl:value-of select="id($target_active_element)//attribute[@name = $attr_name]/@value"/> -->
          <xsl:value-of select="dedek:round(  string(   id($target_active_element)//attribute[@name = $attr_name]/@value   ))"/>
        </text>
      </td>



      <xsl:text disable-output-escaping="yes">
				</xsl:text>


    </tr>
  </xsl:template>



</xsl:stylesheet>
