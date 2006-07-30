<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
          
	
<xsl:template match="/active_list">		

	<xsl:element name="dialog_data">
	
		<xsl:apply-templates select="ferda_box[position()=1]" mode="attributes"/>
		
		<xsl:element name="values">
		
			<xsl:for-each select="ferda_box">
				
				<xsl:element name="value">
					<xsl:for-each select="@*">
						<xsl:attribute name="{name()}"><xsl:value-of select="."/></xsl:attribute>
					</xsl:for-each>	
				</xsl:element>
				
			</xsl:for-each>
			
		</xsl:element>
				
	</xsl:element>
						
</xsl:template>

	
	



	<!-- vypise seznam atributu -->
<xsl:template match="node()" mode="attributes">		

	<xsl:element name="attributes">
	
		<xsl:for-each select="@*">
		
			<xsl:element name="attribute">
				<xsl:attribute name="name"><xsl:value-of select="name()"/></xsl:attribute>
			</xsl:element>
			
		</xsl:for-each>
		
	</xsl:element>

</xsl:template>
	



</xsl:stylesheet>
