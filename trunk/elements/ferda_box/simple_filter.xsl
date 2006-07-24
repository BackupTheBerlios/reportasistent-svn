<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
          
	
<xsl:template match="/active_list">		

	<xsl:element name="dialog_data">
	
		<xsl:apply-templates select="node()[position()=1]" mode="attributes"/>
		
		<xsl:element name="values">
			<xsl:apply-templates select="ferda_box" mode="values"/>
		</xsl:element>
				
	</xsl:element>
						
</xsl:template>

	
	



	<!-- vypise seznam atributu -->
<xsl:template match="node()" mode="attributes">		

	<xsl:element name="attributes">
		<xsl:apply-templates select="@*" mode="attributes"/>
	</xsl:element>

</xsl:template>
	


	<!-- vypise vsechny atributy -->
<xsl:template match="@*" mode="attributes">
	
		<xsl:element name="attribute">
			<xsl:attribute name="name"><xsl:value-of select="name()"/></xsl:attribute>
		</xsl:element>
	
</xsl:template>






	<!-- vypise hodnoty -->
<xsl:template match="node()" mode="values">		
				
	<xsl:element name="value">
		<xsl:for-each select="@*">
		<xsl:variable name="jmeno_atr" select="name()"/>
		<xsl:variable name="hodnota_atr" select="."/>
			<xsl:attribute name="{$jmeno_atr}"><value-of select="{$hodnota_atr}"/></xsl:attribute>
		</xsl:for-each>	
	</xsl:element>

</xsl:template>	
	




</xsl:stylesheet>
