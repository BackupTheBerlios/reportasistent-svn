<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
      
	
	
	<!-- Promenne - nastaveni vizualizaci-->
<xsl:variable name="GraphType">xl3DColumn</xsl:variable>
<xsl:variable name="GraphTitle">KL Graph</xsl:variable>
<xsl:variable name="LegendShow">false</xsl:variable>
<xsl:variable name="GraphWidth">1</xsl:variable>
<xsl:variable name="GraphHeight">0,75</xsl:variable>
	

<xsl:key name="key_ti_attribute" match="ti_attribute" use="@id" />	


	<xsl:template match="hyp_kl"> 
		
		<xsl:variable name="id_base" select="@id" />
		
		<paragraph>
			<graph title="{$GraphTitle}" showlegend="{$LegendShow}" charttype="{$GraphType}" height="{$GraphHeight}" width="{$GraphWidth}" id="{@id}_sdgraph">
			<xsl:variable name="row_attr_id" select="@row_attributes" />
			
			<xsl:for-each select="key('key_ti_attribute',@column_attributes)">
				<xsl:call-template name="column_categories" />  <!-- vypsani kategorii-->
			</xsl:for-each>
			
			<xsl:for-each select="tab[position()=1]/r">
				<xsl:variable name="row_number" select="position()" />	
				<xsl:element name="chart">
					<xsl:attribute name="title"><xsl:value-of select="key('key_ti_attribute',$row_attr_id)/ti_category[position()=$row_number]/@value" /></xsl:attribute>
					<xsl:attribute name="id"><xsl:value-of select="$id_base" />_chart<xsl:value-of select="position()" /></xsl:attribute>
					<xsl:for-each select="c">
						<value value="{@val}" id="{$id_base}_val{position()}" />	
					</xsl:for-each>
				</xsl:element>		
			</xsl:for-each>	
							
			</graph>
		</paragraph>						
	
	</xsl:template>
	
	
	
	<xsl:template name="column_categories" >  <!-- vypise kategorie atributu-->
		
			<categories id="{@id}_col_cats1">
				<xsl:variable name="id_base" select="@id" />
			
				<xsl:for-each select="ti_category" >	
					<category title="{@value}" id="{$id_base}_col_cat{position()}" />
				</xsl:for-each>
			</categories>
			
	</xsl:template>
      




</xsl:stylesheet>
