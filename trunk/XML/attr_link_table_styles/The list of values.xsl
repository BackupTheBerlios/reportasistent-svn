<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
          
	


	<xsl:template match="attr_link_table">
				
		<xsl:text disable-output-escaping="yes">
		</xsl:text>
		<output>

        <xsl:apply-templates select="link">
          <xsl:with-param name="target_active_element">
            <xsl:value-of select="@target"/>
          </xsl:with-param>
        </xsl:apply-templates>


		<xsl:text disable-output-escaping="yes">
		
		</xsl:text>
		</output>
	</xsl:template>




	
	
	<xsl:template match="link">
		<xsl:param name="target_active_element" />
    <xsl:variable name="attr_name" select="@attr_name"/>
    <paragraph id="par">
      <text id="text">
        <xsl:value-of select="id($target_active_element)//attribute[@name = $attr_name]/@value"/>
      </text>
    </paragraph>
	</xsl:template>



</xsl:stylesheet>
