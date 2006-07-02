<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
      
	
	
	<!-- Promenne - nastaveni vizualizaci-->
<xsl:variable name="GraphType">xlColumnClustered</xsl:variable>
<xsl:variable name="LegendShow">true</xsl:variable>
<xsl:variable name="GraphWidth">1</xsl:variable>
<xsl:variable name="GraphHeight">0,75</xsl:variable>
<xsl:variable name="GraphTitle">CF graph</xsl:variable>
	

<xsl:key name="key_ti_attribute" match="ti_attribute" use="@id" />	


	<xsl:template match="hyp_cf"> <!-- nezpomen prepsat na match="/hyp_4ft" - odebrat lomitko -->
		
		<xsl:variable name="id_base" select="@id" />
		
		<paragraph>
			<graph title="{$GraphTitle}" showlegend="{$LegendShow}" charttype="{$GraphType}" height="{$GraphHeight}" width="{$GraphWidth}" id="{@id}_sdgraph">
			
			<xsl:for-each select="key('key_ti_attribute',@attributes)">
				<xsl:call-template name="categories" />  <!-- vypsani kategorii-->
			</xsl:for-each>
				
				<chart title="SD graph" id="chart1">
					<xsl:for-each select="r[position()=1]/c">
						<value value="{@val}" id="{$id_base}_val{position()}" />	
					</xsl:for-each>
				</chart>			
							
			</graph>
		</paragraph>						
	
	</xsl:template>
	
	
	
	<xsl:template name="categories" >  <!-- vypise kategorie atributu-->
		
			<categories id="{@id}_cats1">
				<xsl:variable name="id_base" select="@id" />
			
				<xsl:for-each select="ti_category" >	
					<category title="{@value}" id="{$id_base}_cat{position()}" />
				</xsl:for-each>
			</categories>
			
	</xsl:template>
      




</xsl:stylesheet>