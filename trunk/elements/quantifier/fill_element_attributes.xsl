<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
    
    
    <!-- nastaveni jazyka (defaultne cz) -->
	<xsl:variable name="lng">cz</xsl:variable>	

          
	
	<xsl:template match="quantifier">
				<xsl:text disable-output-escaping="yes">
				</xsl:text>
				<element_attributes>
				
		
		
				<xsl:apply-templates select="@*"/>
				

				<xsl:for-each select="quant_item">
				
					<xsl:call-template name="quant_item_template"/>					
					
				</xsl:for-each>


				<xsl:text disable-output-escaping="yes">
				</xsl:text>
				</element_attributes>
	</xsl:template>






	
	
	<!-- vypise vsechny atributy krome ID-->
	<xsl:template match="@*">
		<xsl:param name="name_prefix" /> 
		<xsl:param name="label_prefix" />

					
				
				<!-- labely polozek-->
		<xsl:variable name="label">
			<xsl:choose>
			
				<!-- nezavisle na jazyce -->
				
				
				
				<!-- cesky -->
				
				<xsl:when test="$lng='cz'">    
						<xsl:choose>
							<xsl:when test="name()='db_name'">
								<xsl:text>Databáze</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='matrix_name'">
								<xsl:text>Datová matice</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='task_name'">
								<xsl:text>Jméno úlohy</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='task_type'">
								<xsl:text>Typ úlohy</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='name'">
								<xsl:text>Název kvantifikátoru</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='type'">
								<xsl:text>Typ kvantifikátoru</xsl:text>
							</xsl:when>
							
							
							<xsl:otherwise>
								<xsl:value-of select="name()"/>
							</xsl:otherwise>
						</xsl:choose>
				</xsl:when>
				
				
				<!-- english-->
				
				<xsl:when test="$lng='en'">	
						<xsl:choose>
							<xsl:when test="name()='db_name'">
								<xsl:text>Database</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='matrix_name'">
								<xsl:text>Data matrix</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='task_name'">
								<xsl:text>Task name</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='task_type'">
								<xsl:text>Task type</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='name'">
								<xsl:text>Quantifier name</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='type'">
								<xsl:text>Quantifier type</xsl:text>
							</xsl:when>
							
							
							<xsl:otherwise>
								<xsl:value-of select="name()"/>
							</xsl:otherwise>
						</xsl:choose>	
				</xsl:when>
				
				<!-- jinak se pouzije nazev XML atributu-->
				
				<xsl:otherwise>
					<xsl:value-of select="name()"/>
				</xsl:otherwise>
				
			</xsl:choose>
		</xsl:variable>
			<!-- end of: labely polozek-->
	
					
					
					
					
					
					<xsl:text disable-output-escaping="yes">
					</xsl:text>
		
		
					<attribute name="{$name_prefix}{name()}" value="{.}" label="{$label_prefix}{$label}" />
	</xsl:template>
	<!-- vypise vsechny atributy -->

	
	
	<!--atribut ID se ignoruje-->
	<xsl:template match="@id">
	</xsl:template>
	






    
    
    <xsl:template name="quant_item_template">
		
					<xsl:text disable-output-escaping="yes">
					</xsl:text>		
		<attribute name="{@name}" value="{@value}" />		
		
	</xsl:template>






    
</xsl:stylesheet>
